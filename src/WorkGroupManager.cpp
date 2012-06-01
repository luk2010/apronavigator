#include "fenIDE.h"

namespace scintilla
{
WorkGroupManager::WorkGroupManager()
{
    workGroup.append(new WorkGroup(new QsciLexerCPP));
}

WorkGroupManager::~WorkGroupManager()
{
    while(workGroup.size() > 0)
        destroyGroup(workGroup[0]);
}

WorkGroupManager::WorkGroup* WorkGroupManager::createGroup()
{
    WorkGroup* group = new WorkGroup(new QsciLexerCPP);
    workGroup.append(group);
    return group;
}

void WorkGroupManager::destroyGroup(WorkGroup *group)
{
    if(group == NULL)
        return;
    workGroup.removeOne(group);
    delete group;
}

WorkGroupManager::WorkGroup* WorkGroupManager::findGroup(documentIDE *doc)
{
    for(unsigned int i = 0; i < workGroup.size(); i++)
    {
        for(unsigned int j = 0; j < workGroup[i]->docList.size(); j++)
        {
            if(workGroup[i]->docList[j] == doc)
                return workGroup[i];
        }
    }
    return NULL;
}

WorkGroupManager::WorkGroup* WorkGroupManager::getDefautGroup()
{
    return workGroup[0];
}

WorkGroupManager::WorkGroup::WorkGroup(QsciLexer *lexer)
{
    QsciAPIs* api = new QsciAPIs(NULL);
    if(lexer!=NULL)
        api->setLexer(lexer);
}

void WorkGroupManager::WorkGroup::addDocument(documentIDE *doc)
{
    docList.append(doc);
    if(lexer!=NULL)
        doc->setLexer(api->lexer());
}
}
