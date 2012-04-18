#include <QDebug>
#include <QCoreApplication>

#include "Version.h"
//#include "ServerConfig.h"
#include "Config/Config.h"

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);

  qDebug() << "Starting backup server -" << qPrintable(versionString());

  //ServerConfig config;
  Config config("../misc/serverconf.xml");
  if (!config.isValid()) {
    qDebug() << "Config not valid for" << config.getPath();
    qDebug() << "Errors:" << config.getErrors();
  }

  ConfigTreeNode *tree = config.parse();
  if (!tree) {
    qDebug() << "Could not parse config.";
    qDebug() << "Errors:" << config.getErrors();    
  }

  //qDebug() << tree;

  ConfigTreeNodeList nodes = tree->searchNodes("ServerConfig/[  * ]/[ 1 ]");
  //ConfigTreeNodeList nodes = tree->searchNodes("ServerConfig/Agents/[*]");
  //ConfigTreeNodeList nodes = tree->searchNodes("[0]/[1]/[2]");  
  qDebug() << nodes;

  /*
  ConfigTreeNode *test = new ConfigTreeNode("test");
  test->addValue("THIS SHOULD NOT BE WRITTEN TO THE FILE");    

  ConfigTreeNode *test2 = new ConfigTreeNode("test2");
  test2->addValue("blaaa");  
  test->addNode(test2);
  
  tree->searchNode("ServerConfig/General")->addNode(test);

  qDebug() << tree;
  */

  config.commit(tree);

  delete tree;
  return app.exec();
}
