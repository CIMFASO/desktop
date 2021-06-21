#include "uiusersrights.h"
#include "ui_usersrights.h"
#include "utils/tableviewdata.h"
#include "utils/checkaccessutil.h"

UI::UsersRights::UsersRights(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UsersRights),
    model(new QStandardItemModel(this)),
    moduleManager(new Model::ModuleManager()),
    listModel(new QStandardItemModel(this))
{
    ui->setupUi(this);

    QSplitter *splitter = new QSplitter;
    tableView = new QTableView;
    treeView = new QTreeView;
    spinner = new WaitingSpinnerWidget(tableView);
    spinner->start();

    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    treeView->setSelectionBehavior(QAbstractItemView::SelectRows);

    tableView->setModel(listModel);
    treeView->setModel(model);
    splitter->addWidget(tableView);
    splitter->addWidget(treeView);
    ui->mainLayout->addWidget(splitter);

    crud->setSelUrl("sel_rule.php");
    crud->setAddUrl("add_rule.php");
    crud->setUpdUrl("upd_rule.php");
    crud->setDelUrl("del_rule.php");

    crud->_select();//select les différents droits
    crud->query("sel_role.php");

    QObject::connect(crud->getHttpObject(),SIGNAL(requestSuccess(QMap<QString,QByteArray>)),this,SLOT(httpResponse(QMap<QString,QByteArray>)));
    connect(tableView,&QTableView::activated,this,&UsersRights::tableItemActivatedSlot);
    connect(model,&QStandardItemModel::itemChanged,this,&UsersRights::itemChanged);
}

UI::UsersRights::~UsersRights()
{
    delete ui;
    delete tableView;
    delete treeView;
    delete moduleManager;
}

void UI::UsersRights::addItemsToTreeViewModel(const int &id)
{
    model->clear();
    QStandardItem *rootItem = model->invisibleRootItem();
    for (Model::Module *m : moduleManager->getListModule()) {
        QStandardItem *item = new QStandardItem(m->getIntitule());
        item->setCheckable(true);

        for(Model::AccessRule a : CheckAccessUtil::getAccessList()){
            if(a.getModule().getIdModule() == m->getIdModule() && a.getRole().getIdRole() == id){
                item->setCheckState(Qt::CheckState::Checked);
                break;
            }
        }

        for (Model::DetailsModule *d : moduleManager->getListDetailModule()) {
            if(d->getModule()->getIdModule() == m->getIdModule() && d->getModule()->getIntitule() == m->getIntitule()){
                QStandardItem *item2 = new QStandardItem(d->getIntitule());
                item2->setCheckable(true);

                if(item->checkState() == Qt::Unchecked)
                    item2->setEnabled(false);

                for(Model::AccessRule a : CheckAccessUtil::getAccessList()){
                    if(a.getDetailModule().getIdDetail() == d->getIdDetail()
                            && a.getModule().getIdModule() == m->getIdModule()
                            && a.getRole().getIdRole() == id){
                        item2->setCheckState(Qt::CheckState::Checked);
                        break;
                    }
                }

                item->appendRow(item2);
            }
        }
        rootItem->appendRow(item);
    }
    treeView->expandAll();
    model->setHeaderData(0,Qt::Horizontal,"Liste des différents accès");
}

void UI::UsersRights::httpResponse(QMap<QString, QByteArray> response)
{
    if(response.firstKey() == Utils::server() + "sel_role.php")
    {
        listModel->clear();
        QJsonArray array = QJsonDocument::fromJson(response.first()).array();
        QStringList headers;
        QList<int> hiddens = {0};
        QList<QStringList> data;
        headers << "ID" << "CODE" << "GROUPE UTILISATEURS";
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array.at(i).toObject();
            QStringList items;
            items << QString::number(obj["IDROLE"].toString().toInt())
                  << obj["CODE"].toString()
                  << obj["LIBELLE"].toString();
            data.append(items);
        }
        if(data.isEmpty()){
            if(spinner->isSpinning())
                spinner->stop();
            spinner->setDataSourceIsEmpty(true);
            spinner->start();
        }else{
            TableViewData::setData(data,hiddens,headers,tableView,listModel,false,false,{},QHeaderView::Stretch);
            if(spinner->isSpinning())
                spinner->stop();
        }

    }

    if(response.firstKey() == crud->getSelUrl())
    {
        CheckAccessUtil::clearAllAccessRule();
        QJsonArray array = QJsonDocument::fromJson(response.first()).array();
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array.at(i).toObject();
            Model::Module module;
            module.setIdModule(obj["IDMODULE"].toString().toInt());
            Model::DetailsModule detail;
            detail.setIdDetail(obj["IDDETAILSMODULE"].toString().toInt());
            Model::Role role;
            role.setIdRole(obj["IDROLE"].toString().toInt());
            Model::AccessRule rule;
            rule.setRole(role);
            rule.setModule(module);
            rule.setDetailModule(detail);
            rule.setAccess(obj["ACCESS"].toString().toInt() == 1 ? true : false);
            CheckAccessUtil::addAccessRule(rule);
        }
    }

    if(response.firstKey() == crud->getAddUrl()){
        QJsonObject object = QJsonDocument::fromJson(response.first()).object();
        QString result = object["Response"].toString();
        if(result == "Ok"){
            crud->_select();
        }
    }
}

void UI::UsersRights::itemChanged(QStandardItem *item)
{
    if(item->hasChildren()){
        for (int i = 0; i < item->rowCount(); ++i) {

            QStandardItem *child = item->child(i);
            child->setEnabled(item->checkState());

            Model::AccessRule *rule = new Model::AccessRule;
            Model::Module module;
            Model::DetailsModule detail;
            Model::Role role;

            role.setIdRole(currentRoleId);
            module.setIdModule(moduleManager->getModuleByName(item->text())->getIdModule());
            detail.setIdDetail(moduleManager->getDetailModuleByName(child->text())->getIdDetail());

            rule->setAccess(true);
            rule->setRole(role);
            rule->setModule(module);
            rule->setDetailModule(detail);

            if(item->checkState() == Qt::Checked && child->checkState() == Qt::Checked)
                crud->_create(rule);
            else if(item->checkState() == Qt::Unchecked && child->checkState() == Qt::Unchecked)
                crud->_delete(rule);
            delete rule;
        }
    }

    if(!item->hasChildren()){
        if(item->parent()->checkState() == Qt::Checked){

            Model::AccessRule *rule = new Model::AccessRule;
            Model::Module module;
            Model::DetailsModule detail;
            Model::Role role;

            role.setIdRole(currentRoleId);
            module.setIdModule(moduleManager->getModuleByName(item->parent()->text())->getIdModule());
            detail.setIdDetail(moduleManager->getDetailModuleByName(item->text())->getIdDetail());

            rule->setAccess(true);
            rule->setRole(role);
            rule->setModule(module);
            rule->setDetailModule(detail);

            if(item->checkState() == Qt::Checked)
                crud->_create(rule);
            else if(item->checkState() == Qt::Unchecked)
                crud->_delete(rule);
            delete rule;
        }
    }
}

void UI::UsersRights::tableItemActivatedSlot(const QModelIndex &index)
{
    currentRoleId = index.sibling(index.row(),0).data().toInt();
    crud->_select();
    addItemsToTreeViewModel(currentRoleId);
}
