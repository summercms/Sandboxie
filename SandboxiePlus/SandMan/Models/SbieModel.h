#pragma once
#include <qwidget.h>
#include "../../QSbieAPI/Sandboxie/SandBox.h"
#include "../../MiscHelpers/Common/TreeItemModel.h"


class CSbieModel : public CTreeItemModel
{
    Q_OBJECT

public:
    CSbieModel(QObject *parent = 0);
	~CSbieModel();

	QList<QVariant>	Sync(const QMap<QString, CSandBoxPtr>& BoxList);

	CSandBoxPtr		GetSandBox(const QModelIndex &index) const;
	CBoxedProcessPtr GetProcess(const QModelIndex &index) const;

	int				columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant		headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

	enum EColumns
	{
		eName = 0,
		eProcessId,
		eStatus,
		//eTitle,
		//eLogCount,
		eTimeStamp,
		eCount
	};

protected:
	bool			Sync(const CSandBoxPtr& pBox, const QMap<quint64, CBoxedProcessPtr>& ProcessList, QMap<QList<QVariant>, QList<STreeNode*> >& New, QHash<QVariant, STreeNode*>& Old, QList<QVariant>& Added);

	struct SSandBoxNode: STreeNode
	{
		SSandBoxNode(const QVariant& Id) : STreeNode(Id) { inUse = -1; }

		CSandBoxPtr	pBox;
		int			inUse;

		CBoxedProcessPtr pProcess;
	};

	virtual STreeNode*		MkNode(const QVariant& Id) { return new SSandBoxNode(Id); }

	QList<QVariant>			MakeProcPath(const QString& BoxName, const CBoxedProcessPtr& pProcess, const QMap<quint64, CBoxedProcessPtr>& ProcessList);
	QList<QVariant>			MakeProcPath(const CBoxedProcessPtr& pProcess, const QMap<quint64, CBoxedProcessPtr>& ProcessList);
	bool					TestProcPath(const QList<QVariant>& Path, const QString& BoxName, const CBoxedProcessPtr& pProcess, const QMap<quint64, CBoxedProcessPtr>& ProcessList, int Index = 0);

	//virtual QVariant		GetDefaultIcon() const;

private:
	QIcon m_BoxEmpty;
	QIcon m_BoxInUse;
	QIcon m_ExeIcon;
};