// main.cpp
//
// Copyright 2014, Timothy Howe <timh at deschutesdigital dot com>
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//////////

// A program to parse XML from the www.localcallinguide.com into CSV

#include <QCoreApplication>

#include <QString>
#include <QVariant>
#include <QMap>
#include <QList>
#include <QFile>
#include <QRegExp>
#include <QTextStream>

// Ths is our xml stream parsing object stuff.
#include "lcgxmlparser.h"

// Instead of the normal cout C++ stream object, we use a
// QTextStream to do the same job.  This way we take
// advantage of Qt4 UTF-8 capability.
static QTextStream qcout(stdout, QIODevice::WriteOnly);
QTextStream& cout() { return qcout; }

int main(int argc, char *argv[])
{
    // This is not a GUI Qt4 app...
    QCoreApplication app(argc, argv);

    QFile inputFile;
    LcgXmlParser parser;

    QMap<QString, QVariant> prefix_data;
    QList< QMap<QString, QVariant> > prefix_data_list;

    // regex for checking NOT valid characters
    QRegExp vrx("[^a-zA-Z0-9\\,\\.\\-\\'\\s]");

    // If a file name is specified, parse it, otherwise
    // assume input from STDIN.
    if(argv[1])
    {
        inputFile.setFileName(argv[1]);
        if(!inputFile.open(QIODevice::ReadOnly))
        {
            cout() << "Error: Cannot read file " << ": "
                      << inputFile.errorString() << endl;
        };
    }
    else
    {
        if(!inputFile.open(stdin, QIODevice::ReadOnly))
        {
            cout() << "Error: Cannot read from STDIN " << ": "
                      << inputFile.errorString() << endl;
        };
    }

    // This puts our XML stream parser to work.
    parser.setFile(&inputFile);
    parser.parseFile();
    prefix_data_list = parser.result();

    // and finally we can spit the data out
    for (int i = 0; i < prefix_data_list.size(); ++i)
    {
        prefix_data = prefix_data_list.value(i);
        cout() << prefix_data["npa"].toString().toUtf8() << ","
               << prefix_data["nxx"].toString().toUtf8() << ","
               << prefix_data["block"].toString().toUtf8() << ","
               << prefix_data["exchange"].toString().toUtf8() << ","
               << prefix_data["rate_center"].toString().toUtf8() << ","
               << prefix_data["region"].toString().toUtf8() << ","
               << prefix_data["switch"].toString().toUtf8() << ","
               << prefix_data["ocn"].toString().toUtf8() << ","
               << "\"" << prefix_data["company_name"].toString().remove(vrx).toUtf8() << "\","
               << prefix_data["ilec_ocn"].toString().toUtf8() << ","
               << "\"" << prefix_data["ilec_name"].toString().remove(vrx).toUtf8() << "\","
               << prefix_data["lata"].toString().toUtf8() << endl;
    }
}
