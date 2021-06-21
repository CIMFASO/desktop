#include "uiusersroles.h"
#include "ui_uiusersroles.h"

UI::UsersRoles::UsersRoles(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UsersRoles),
    model(new QStandardItemModel(this)),
    listModel(new QStandardItemModel(this))
{
    ui->setupUi(this);

    QSplitter *splitter = new QSplitter;
    tableView = new QTableView;
    treeView = new QTreeView;
    spinner =new WaitingSpinnerWidget(tableView);
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

    crud->setSelUrl("sel_user_roles.php");
    crud->setAddUrl("add_user_role.php");
    crud->setUpdUrl("upd_user_role.php");
    crud->setDelUrl("del_user_role.php");

    crud->_select();//select les différents droits
    crud->query("sel_user.php");
    crud->query("sel_role.php");

    QObject::connect(crud->getHttpObject(),SIGNAL(requestSuccess(QMap<QString,QByteArray>)),this,SLOT(httpResponse(QMap<QString,QByteArray>)));
    connect(tableView,&QTableView::activated,this,&UsersRoles::tableItemActivatedSlot);
    connect(model,&QStandardItemModel::itemChanged,this,&UsersRoles::itemChanged);
}

UI::UsersRoles::~UsersRoles()
{
    delete ui;
    delete tableView;
    delete treeView;
}

void UI::UsersRoles::addItemsToTreeViewModel(const int &id)
{
    model->clear();
    QStandardItem *rootItem = model->invisibleRootItem();
    for (Model::Role r : roles) {
        QStandardItem *item = new QStandardItem(r.getLibelle());
        item->setCheckable(true);

        for(Model::UserRoles ur : userRoles)
        {
            if(ur.getUser().getIdUser() == id && r.getIdRole() == ur.getRole().getIdRole() && item->checkState() != Qt::CheckState::Checked)
            {
                item->setCheckState(Qt::CheckState::Checked);
                break;
            }
        }

        rootItem->appendRow(item);
    }
    treeView->expandAll();
    model->setHeaderData(0,Qt::Horizontal,"Liste des différents roles");
}

void UI::UsersRoles::httpResponse(QMap<QString, QByteArray> response)
{
    if(response.firstKey() == Utils::server() + "sel_user.php")
    {
        listModel->clear();
        QJsonArray array = QJsonDocument::fromJson(response.first()).array();
        QStringList headers;
        QList<int> hiddens = {0};
        QList<QStringList> data;
        headers << "ID" << "NOM" << "PRENOM"<<"LOGIN";
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array.at(i).toObject();
            QStringList items;
            items << QString::number(obj["ID_USER"].toString().toInt())
                  << obj["NOM_USER"].toString()
                  << obj["PRENOM_USER"].toString()
                  << obj["LOGIN"].toString();
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
        userRoles.clear();
        QJsonArray array = QJsonDocument::fromJson(response.first()).array();
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array.at(i).toObject();
            Model::UserRoles uRole;
            Model::Role role;
            Model::User user;
            role.setIdRole(obj["IDROLE"].toString().toInt());
            role.setCode(obj["CODE"].toString());
            role.setLibelle(obj["LIBELLE"].toString());
            user.setIdUser(obj["ID_USER"].toString().toInt());
            user.setNom(obj["NOM_USER"].toString());
            user.setLogin(obj["LOGIN"].toString());
            user.setPrenom(obj["PRENOM_USER"].toString());
            user.setTelephone(obj["TELEPHONE"].toString());
            uRole.setRole(role);
            uRole.setUser(user);
            userRoles.append(uRole);
        }
    }

    if(response.firstKey() == Utils::server() + "sel_role.php")
    {
        roles.clear();
        QJsonArray array = QJsonDocument::fromJson(response.first()).array();
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array.at(i).toObject();
            Model::Role role;
            role.setIdRole(obj["IDROLE"].toString().toInt());
            role.setCode(obj["CODE"].toString());
            role.setLibelle(obj["LIBELLE"].toString());
            roles.append(role);
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

void UI::UsersRoles::itemChanged(QStandardItem *item)
{
    Model::UserRoles *userRole = new Model::UserRoles();
    Model::User user;
    Model::Role role;
    user.setIdUser(currentUserId);
    role.setIdRole(roles.at(item->row()).getIdRole());
    userRole->setRole(role);
    userRole->setUser(user);
    if(item->checkState() == Qt::Checked)
        crud->_create(userRole);
    else if(item->checkState() == Qt::Unchecked)
        crud->_delete(userRole);
    delete userRole;
}

void UI::UsersRoles::tableItemActivatedSlot(const QModelIndex &index)
{
    currentUserId = index.sibling(index.row(),0).data().toInt();
    crud->_select();
    addItemsToTreeViewModel(currentUserId);
}
