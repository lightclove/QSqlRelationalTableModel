#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{

}

/* Методы для подключения к базе данных
 * */
void DataBase::connectToDataBase()
{
    /* см. статью про QSqlTableModel */
}

/* Методы восстановления базы данных
 * */
bool DataBase::restoreDataBase()
{
    if(this->openDataBase()){
        if((!this->createMainTable()) || (!this->createDeviceTable())){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

/* Метод для открытия базы данных
 * */
bool DataBase::openDataBase()
{
    /* см. статью про QSqlTableModel */
}

/* Методы закрытия базы данных
 * */
void DataBase::closeDataBase()
{
    db.close();
}

/* Метод для создания основной таблицы в базе данных
 * */
bool DataBase::createMainTable()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " TABLE " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            TABLE_DATE      " DATE            NOT NULL,"
                            TABLE_TIME      " TIME            NOT NULL,"
                            TABLE_HOSTNAME  " INTEGER         NOT NULL,"
                            TABLE_IP        " INTEGER         NOT NULL"
                        " )"
                    )){
        qDebug() << "DataBase: error of create " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

/* Метод для создания таблицы устройств в базе данных
 * */
bool DataBase::createDeviceTable()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " DEVICE " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            DEVICE_HOSTNAME  " VARCHAR(255)    NOT NULL,"
                            DEVICE_IP        " VARCHAR(16)     NOT NULL"
                        " )"
                    )){
        qDebug() << "DataBase: error of create " << DEVICE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

/* Метод для вставки записи в основную таблицу
 * */
bool DataBase::inserIntoMainTable(const QVariantList &data)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("INSERT INTO " TABLE " ( " TABLE_DATE ", "
                                             TABLE_TIME ", "
                                             TABLE_HOSTNAME ", "
                                             TABLE_IP " ) "
                  "VALUES (:Date, :Time, :Hostname, :IP )");
    query.bindValue(":Date",        data[0].toDate());
    query.bindValue(":Time",        data[1].toTime());
    query.bindValue(":Hostname",    data[2].toInt());
    query.bindValue(":IP",          data[3].toInt());
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

/* Метод для вставки записи в таблицу устройств
 * */
bool DataBase::inserIntoDeviceTable(const QVariantList &data)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("INSERT INTO " DEVICE " ( " DEVICE_HOSTNAME ", "
                                              DEVICE_IP " ) "
                  "VALUES (:Hostname, :IP )");
    query.bindValue(":Hostname",    data[0].toString());
    query.bindValue(":IP",          data[1].toString());
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << DEVICE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}
