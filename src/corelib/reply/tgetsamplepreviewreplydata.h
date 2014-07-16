#ifndef TGETSAMPLEPREVIEWREPLYDATA_H
#define TGETSAMPLEPREVIEWREPLYDATA_H

class TGetSamplePreviewReplyDataPrivate;

class TBinaryFile;
class TBinaryFileList;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetSamplePreviewReplyData ==================
============================================================================*/

class T_CORE_EXPORT TGetSamplePreviewReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetSamplePreviewReplyData)
public:
    explicit TGetSamplePreviewReplyData();
    TGetSamplePreviewReplyData(const TGetSamplePreviewReplyData &other);
    ~TGetSamplePreviewReplyData();
public:
    TBinaryFileList &extraFiles();
    const TBinaryFileList &extraFiles() const;
    TBinaryFile &mainFile();
    const TBinaryFile &mainFile() const;
    void setExtraFiles(const TBinaryFileList &extraFiles);
    void setMainFile(const TBinaryFile &file);
public:
    TGetSamplePreviewReplyData &operator =(const TGetSamplePreviewReplyData &other);
    bool operator ==(const TGetSamplePreviewReplyData &other) const;
    bool operator !=(const TGetSamplePreviewReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetSamplePreviewReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetSamplePreviewReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TGetSamplePreviewReplyData &data);
};

Q_DECLARE_METATYPE(TGetSamplePreviewReplyData)

#endif // TGETSAMPLEPREVIEWREPLYDATA_H
