// lcgxmlparser.cpp
//
// Please see lcgxmlparser.h file for license information.

// The LcgXmlParser class

#include <QFile>
#include <QXmlStreamReader>
#include <QString>
#include <QVariant>

//#include <QtDebug>

#include "lcgxmlparser.h"

LcgXmlParser::LcgXmlParser()
{
    file_ = 0;	// initialize the file pointer
    parse_success = true;
}

LcgXmlParser::LcgXmlParser(QFile *file)
{
    file_ = file;
}

bool LcgXmlParser::parseFile()
{
    bool first_prefixdata = true;
    prefix_data_.clear();
    prefix_data_list_.clear();

    // to hold the grabbed string for multiple use
    // (like if I need to output some debug info)
    // Otherwise, when you read the element, it
    // is automatically advanced, so if you try to
    // read it again for debug info, it isn't the
    // same thing, thus the reusable holder.
    QString scratch;

    reader.readNext();
    while(!reader.atEnd()) {
        if(reader.isStartElement())
        {
            if(reader.name() == "prefixdata")
            {
                // If this is the first prefixdata element
                // then there isn't much to do until the
                // next one.  On all others, we want to put
                // the data into the list and prepare to
                // get more data.
                if(first_prefixdata)
                {
                    first_prefixdata = false;
                }
                else
                {
                    prefix_data_list_.append(prefix_data_);
                    prefix_data_.clear();
                }
            }
            else if(reader.name() == "npa")
            {
                scratch = reader.readElementText();
                prefix_data_.insert(QString("npa"), QVariant(scratch));
            }
            else if(reader.name() == "nxx")
            {
                scratch = reader.readElementText();
                prefix_data_.insert(QString("nxx"), QVariant(scratch));
            }
            else if(reader.name() == "x")
            {
                scratch = reader.readElementText();
                prefix_data_.insert(QString("block"), QVariant(scratch));
            }
            else if(reader.name() == "exch")
            {
                scratch = reader.readElementText();
                prefix_data_.insert(QString("exchange"), QVariant(scratch));
            }
            else if(reader.name() == "rc")
            {
                scratch = reader.readElementText();
                prefix_data_.insert(QString("rate_center"), QVariant(scratch));
            }
            else if(reader.name() == "region")
            {
                scratch = reader.readElementText();
                prefix_data_.insert(QString("region"), QVariant(scratch));
            }
            else if(reader.name() == "switch")
            {
                scratch = reader.readElementText();
                prefix_data_.insert(QString("switch"), QVariant(scratch));
            }
            else if(reader.name() == "ocn")
            {
                scratch = reader.readElementText();
                prefix_data_.insert(QString("ocn"), QVariant(scratch));
            }
            else if(reader.name() == "company-name")
            {
                scratch = reader.readElementText();
                prefix_data_.insert(QString("company_name"), QVariant(scratch));
            }
            else if(reader.name() == "ilec-ocn")
            {
                scratch = reader.readElementText();
                prefix_data_.insert(QString("ilec_ocn"), QVariant(scratch));
            }
            else if(reader.name() == "ilec-name")
            {
                scratch = reader.readElementText();
                prefix_data_.insert(QString("ilec_name"), QVariant(scratch));
            }
            else if(reader.name() == "lata")
            {
                scratch = reader.readElementText();
                prefix_data_.insert(QString("lata"), QVariant(scratch));
            }
        }
        reader.readNext();
    }

    // There should be one more map to add after
    // the XML file is done.
    if(!prefix_data_.isEmpty())
    {
        prefix_data_list_.append(prefix_data_);
    }

    // We should probably add some data validation code so
    // that this error can be meaningful (or even exist).
    return parse_success;
}

LcgXmlParser::~LcgXmlParser()
{
}
