#include "..\head\administrator.h"

void copyfile(const char* source, const char* destination) {
    FILE *src = fopen(source, "r");
    if (src == NULL) {
        printf("无法打开源文件: %s\n", source);
        return;
    }

    FILE *dest = fopen(destination, "w");
    if (dest == NULL) {
        printf("无法打开目标文件: %s\n", destination);
        fclose(src);
        return;
    }

    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytesRead, dest);
    }

    fclose(src);
    fclose(dest);
}

void backupData() {
    saveData();
    copyfile("../data/userdata.csv", "../backup/userdata_backup.csv");
    copyfile("../data/all_apartment.csv", "../backup/all_apartment_backup.csv");
    copyfile("../data/all_staff.csv", "../backup/all_staff_backup.csv");
    copyfile("../data/holidaydata.csv", "../backup/holidaydata_backup.csv");
    copyfile("../data/holidayquotadata.csv", "../backup/holidayquotadata_backup.csv");
    copyfile("../data/leave_applications.csv", "../backup/leave_applications.csv_backup.csv");
    printf("数据备份完成！\n");
}

void restoreData() {
    char confirm;

    printf("恢复会覆盖当前数据，是否继续？(y/n): ");
    scanf(" %c", &confirm);

    if (confirm != 'y') {
        printf("已取消恢复。\n");
        return;
    }

    copyfile("../backup/userdata_backup.csv", "../data/userdata.csv");
    copyfile("../backup/all_apartment_backup.csv", "../data/all_apartment.csv");
    copyfile("../backup/all_staff_backup.csv", "../data/all_staff.csv");
    copyfile("../backup/holidaydata_backup.csv", "../data/holidaydata.csv");
    copyfile("../backup/holidayquotadata_backup.csv", "../data/holidayquotadata.csv");
    copyfile("../backup/leave_applications.csv_backup.csv", "../data/leave_applications.csv");

    loadData();
    printf("数据恢复完成！\n");
}