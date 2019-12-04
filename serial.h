#ifndef SERIAL_H
#define SERIAL_H

#include <QString>
#include <QObject>
#include <QProcess>
#include <QByteArray>
#include <string.h>
#include <libudev.h>
#include <sys/stat.h>



QString getSerial(){
    struct udev            *ud      = NULL;
    struct stat            statbuf;
    struct udev_device     *device  = NULL;
    struct udev_list_entry *entry   = NULL;

    QString serialNum;

    ud = udev_new();
    if (NULL == ud) {
        qWarning()<<"Failed to create udev.\n";
    } else {
        if (0 != stat("/dev/sda", &statbuf)) {
            qWarning()<<"Failed to stat /dev/sda.\n";
        } else {
            device = udev_device_new_from_devnum(ud, 'b', statbuf.st_rdev);
            if (NULL == device) {
                qWarning()<<"Failed to open /dev/sda.\n";
            } else {
                entry = udev_device_get_properties_list_entry(device);
                while (NULL != entry) {
                    if (0 == strcmp(udev_list_entry_get_name(entry),
                                    "ID_SERIAL")) {
                        break;
                    }
                    entry = udev_list_entry_get_next(entry);
                }

//                printf("Serial ID: %s\n", udev_list_entry_get_value(entry));
                serialNum = udev_list_entry_get_value(entry);
                udev_device_unref(device);
            }
        }
        (void)udev_unref(ud);
    }
    return serialNum;
}


#endif // SERIAL_H

