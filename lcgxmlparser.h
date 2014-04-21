// lcgxmlparser.h
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

// --------------------------------------------------------------
// The LcgXmlParser class can take a Local Calling Guide XML file
// as returned by something like:
// http://www.localcallingguide.com/xmlprefix.php?npa=234
// or
// http://www.localcallingguide.com/xmlprefix.php?npa=250&nxx=423
//
// This will already be a prepared file, or piped to the main
// program with cURL or something similar.
//
// A QList<QMap> will be returned with the results of parsing
// the XML.  (grabbing only the stuff we want)
//
// The map contains the following fields:
// npa,nxx,block,exchange,rate_center,region,switch,ocn,company_name,ilec_ocn,ilec_name,lata
// --------------------------------------------------------------

#ifndef LCGXMLPARSER_H
#define LCGXMLPARSER_H

#include <QFile>
#include <QMap>
#include <QList>
#include <QString>
#include <QVariant>
#include <QXmlStreamReader>

class LcgXmlParser
{
public:
    LcgXmlParser();	// default constructor
    LcgXmlParser(QFile *file);	// construct with file
    virtual ~LcgXmlParser();	// destructor

    // set the file to be used
    void setFile(QFile *file);

    // parse the file returning the parse_success bool
    bool parseFile();

    // return the prefix_data_list_
    const QList< QMap<QString, QVariant> > &result() const;

private:
    QFile *file_;
    QXmlStreamReader reader;
    bool parse_success;
    QMap<QString, QVariant> prefix_data_;
    QList< QMap<QString, QVariant> > prefix_data_list_;
};

inline void LcgXmlParser::setFile(QFile *file)
{
    file_ = file;
    reader.setDevice(file_);
}

inline const QList< QMap<QString, QVariant> > &LcgXmlParser::result() const
{
    return prefix_data_list_;
}

#endif	// LCGXMLPARSER_H
