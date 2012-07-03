// HEXplorer is an Asap and HEX file editor
// Copyright (C) 2011  <Christophe Hoel>
//
// This file is part of HEXplorer.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// please contact the author at : christophe.hoel@gmail.com

#ifndef SrecFile_H
#define SrecFile_H

#include <string>
#include <QStringList>
#include <omp.h>
#include "node.h"
#include "datacontainer.h"
class WorkProject;
class CHARACTERISTIC;
class AXIS_PTS;
class MODULE;
class Data;
class PROJECT;
class MEMORY_SEGMENT;

class MemBlock;

using namespace std;

class SrecFile : public QObject, public DataContainer
{
    Q_OBJECT

    public:
        SrecFile(QString fullSrecFileName, WorkProject *parentWP, QString module, QObject *parent = 0);
        ~SrecFile();

        // members
        Node* record_layout;
        Node* compu_method;
        Node* compu_vtab;
        QStringList listNotValidData;

        // methods
        void attach(QObject*o);
        int getNumByte(std::string str);
        void exportSubsetList2Csv(QStringList subsetList);
        void exportSubsetList2Cdf(QStringList subsetList);
        bool isValidAddress(QString address);
        bool read();
        void verify();
        void checkDisplay();
        void setFullName(QString fullName);
        QStringList writeHex();
        QString getHexValue(QString address, int offset, int nByte);
        QStringList getHexValues(QString address, int offset, int nByte, int size);
        QList<double> getDecValues(double address, int nByte, int size, std::string type);
        QString fullName();
        QList<int> checkFmtcMonotony(bool *bl);
        std::string pixmap();
        Data* readLabel(CHARACTERISTIC *label, bool phys);
        Data* readLabel(AXIS_PTS *label, bool phys);
        PROJECT *getA2lFileProject();

    public slots:
        void detach(QObject*o);
        Data* getData(QString str);
        QString toString();


    private:

        // members
        omp_lock_t lock;
        int fileLinesNum;
        int maxValueProgbar;
        int valueProgBar;
        PROJECT *a2lProject;
        QList<MemBlock*> blockList;
        int refCount;
        QList<QObject*> owners;
        QString fullSrecName;
        QString byteOrder;
        QHash<QString,int> nByte;
        QList<uint> listMemSegData;


        static int asciiToByte[256*256];

        // methods
        void incrementValueProgBar(int n);
        bool parseFile();
        void readAllData();
        bool isA2lCombined();
        void hex2MemBlock(Data* data);
        bool modifiedData2block();
        QStringList block2list();
        void setValue(unsigned int IAddr, QString hex, int nByte);
        void setValues(unsigned int IAddr, QStringList hexList, int nByte);
        QString checksum(QString str);
        unsigned int tzn(unsigned int v);
        QString dec2hex(double dec, std::string type);

    signals:
        //void lineParsed(int,int);
        void progress(int,int);
};

#endif // SrecFile_H
