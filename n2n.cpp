#include "n2n.h"
#include <QCoreApplication>

n2n::n2n()
{
    lujing = QCoreApplication::applicationDirPath() + "\\n2n_client\\x64\\edge_v3_bugxia_n2n.exe";
    canshu.append("-I BEA0E17CA279 -c f7NrgB7pYq -l ip");
}
