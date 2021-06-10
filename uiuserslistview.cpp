#include "uiuserslistview.h"
#include "ui_uiuserslistview.h"
#include "uiusers.h"
#include "utils/tableviewdata.h"

UIUsersListview::UIUsersListview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIUsersListview)
{
    ui->setupUi(this);

    spinner = new WaitingSpinnerWidget(ui->tableView);
    delegate = new CustomDelegate(ui->tableView);
    sortModel = new QSortFilterProxyModel(this);

    ui->tableView->setItemDelegate(delegate);
    sortModel->setSourceModel(model);
    ui->tableView->setModel(sortModel);

    crud->setAddUrl("add_user.php");
    crud->setDelUrl("del_user.php");
    crud->setUpdUrl("upd_user.php");
    crud->setSelUrl("sel_users.php");

    crud->_select();

    connect(delegate,&CustomDelegate::delButtonClicked,this,&UIUsersListview::slotDelete);
    connect(delegate,&CustomDelegate::updButtonClicked,this,&UIUsersListview::slotUpdate);
    connect(crud->getHttpObject(),&HttpRequest::requestSuccess,this,&UIUsersListview::httpResponse);
}

UIUsersListview::~UIUsersListview()
{
    delete ui;
}

void UIUsersListview::httpResponse(QMap<QString, QByteArray> response)
{
    if(response.firstKey().contains(crud->getAddUrl())
            || response.firstKey().contains(crud->getDelUrl())
            || response.firstKey().contains(crud->getUpdUrl()))
    {
        QJsonObject object = QJsonDocument::fromJson(response.first()).object();
        QString result = object["Response"].toString();
        if(result == "Ok"){
            emit success();
            crud->_select();
        }else{
            MessageBox::error(this);
        }
    }

    if(response.firstKey().contains(crud->getSelUrl())){
        model->clear();
        delegate->setCustomColumn(5);

        QJsonArray array = QJsonDocument::fromJson(response.first()).array();
        QStringList headers = {"ID","NOM","LOGIN","EMAIL","TELEPHONE","ACTIONS"};

        QList<QStringList> data;
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array.at(i).toObject();
            QStringList items;
            items << QString::number(obj["ID"].toInt())
                  << obj["NOM_USER"].toString()
                  << obj["LOGIN"].toString()
                  << obj["MAIL"].toString()
                  << obj["TELEPHONE"].toString()
                  << "";
           data.append(items);
        }
        if(data.isEmpty()){
            if(spinner->isSpinning())
                spinner->stop();
            spinner->setDataSourceIsEmpty(true);
            spinner->start();
        }else{
            TableViewData::setData(data,{0},headers,ui->tableView,model,true,false,{},QHeaderView::Stretch);
            if(spinner->isSpinning())
                spinner->stop();
        }
    }
}

void UIUsersListview::slotUpdate(const QModelIndex &index)
{
    UIUsers *ui = new UIUsers(this);
    Model::User m;
    m.setIdUser(index.sibling(index.row(),0).data().toInt());
    m.setNom(index.sibling(index.row(),1).data().toString());
    m.setEmail(index.sibling(index.row(),3).data().toString());
    m.setTelephone(index.sibling(index.row(),4).data().toString());
    //m.setPassword(index.sibling(index.row(),4).data().toString());

    ui->setUser(m);
    ui->setMode("Modifier");

    connect(ui,&UIUsers::update,this,[=](const Model::User &g){
       crud->_update(&g);
    });
    connect(this,&UIUsersListview::success,ui,&UIUsers::close);

    ui->exec();
}

void UIUsersListview::slotDelete(const QModelIndex &index)
{
    if(MessageBox::confirmDelete(this)){
        Model::User u;
        u.setIdUser(index.sibling(index.row(),0).data().toInt());
        crud->_delete(&u);
    }
}

void UIUsersListview::on_newButton_clicked()
{
    UIUsers *u = new UIUsers(this);
    connect(u,&UIUsers::create,this,[=](const Model::User &user){
        crud->_create(&user);
    });
    connect(this,&UIUsersListview::success,u,&UIUsers::close);
    u->exec();
}

void UIUsersListview::on_nomLineEdit_textChanged(const QString &arg1)
{
    sortModel->setFilterKeyColumn(1);
    sortModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    sortModel->setFilterRegExp(arg1);
}
