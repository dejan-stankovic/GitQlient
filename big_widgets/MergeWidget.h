#pragma once

#include <QFrame>
#include <QMap>

class GitBase;
class QVBoxLayout;
class QPushButton;
class QStackedWidget;
class MergeInfoWidget;
class QLineEdit;
class QTextEdit;
class FileDiffWidget;
class RevisionFiles;
class RevisionsCache;

class ConflictButton : public QFrame
{
   Q_OBJECT

signals:
   void changeDiffView(bool checked);

public:
   explicit ConflictButton(const QString &filename, QWidget *parent = nullptr);

   void setChecked(bool checked);

private:
   QPushButton *mFile = nullptr;
   QPushButton *mResolve = nullptr;
   QPushButton *mUpdate = nullptr;
};

class MergeWidget : public QFrame
{
   Q_OBJECT

signals:
   void signalMergeFinished();

public:
   explicit MergeWidget(const QSharedPointer<RevisionsCache> &gitQlientCache, const QSharedPointer<GitBase> &git,
                        QWidget *parent = nullptr);

   void configure(const RevisionFiles &files);

private:
   QSharedPointer<RevisionsCache> mGitQlientCache;
   QSharedPointer<GitBase> mGit;
   QVBoxLayout *mConflictBtnContainer = nullptr;
   QVBoxLayout *mAutoMergedBtnContainer = nullptr;
   QStackedWidget *mCenterStackedWidget = nullptr;
   QLineEdit *mCommitTitle = nullptr;
   QTextEdit *mDescription = nullptr;
   QPushButton *mMergeBtn = nullptr;
   QPushButton *mAbortBtn = nullptr;
   QMap<ConflictButton *, FileDiffWidget *> mConflictButtons;

   void fillButtonFileList(const RevisionFiles &files);
   void changeDiffView(bool fileBtnChecked);
   void abort();
   void commit();
   void removeMergeComponents();
};
