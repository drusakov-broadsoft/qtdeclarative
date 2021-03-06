/****************************************************************************
**
** Copyright (C) 2016 Canonical Limited and/or its subsidiary(-ies).
** Contact: https://www.qt.io/licensing/
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtTest/QtTest>
#include <QtQml/qqmlengine.h>
#include <QtQuick/qquickview.h>
#include <QtQuick/qquickitem.h>
#include "../../shared/util.h"

class tst_QQMLTypeLoader : public QQmlDataTest
{
    Q_OBJECT

private slots:
    void testLoadComplete();
    void loadComponentSynchronously();
};

void tst_QQMLTypeLoader::testLoadComplete()
{
    QQuickView *window = new QQuickView();
    window->engine()->addImportPath(QT_TESTCASE_BUILDDIR);
    qDebug() << window->engine()->importPathList();
    window->setGeometry(0,0,240,320);
    window->setSource(testFileUrl("test_load_complete.qml"));
    window->show();
    QVERIFY(QTest::qWaitForWindowExposed(window));

    QObject *rootObject = window->rootObject();
    QTRY_VERIFY(rootObject != 0);
    QTRY_COMPARE(rootObject->property("created").toInt(), 2);
    QTRY_COMPARE(rootObject->property("loaded").toInt(), 2);
    delete window;
}

void tst_QQMLTypeLoader::loadComponentSynchronously()
{
    QQmlEngine engine;
    QTest::ignoreMessage(QtWarningMsg, QRegularExpression(
                             QLatin1String(".*nonprotocol::1:1: QtObject is not a type.*")));
    QQmlComponent component(&engine, testFileUrl("load_synchronous.qml"));
    QObject *o = component.create();
    QVERIFY(o);
}

QTEST_MAIN(tst_QQMLTypeLoader)

#include "tst_qqmltypeloader.moc"
