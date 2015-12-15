/*
  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2010-2015 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Funk <kevin.funk@kdab.com>

  Licensees holding valid commercial KDAB GammaRay licenses may use this file in
  accordance with GammaRay Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAMMARAY_STATEMACHINEVIEWER_GVGRAPH_H
#define GAMMARAY_STATEMACHINEVIEWER_GVGRAPH_H

#include "gvgraphelements.h"
#include "gvtypes.h"

#include <graphviz/types.h>

#include <QFont>
#include <QHash>
#include <QString>

namespace GammaRay {

typedef QPair<NodeId, GVNode> GVNodePair;
typedef QPair<EdgeId, GVEdge> GVEdgePair;
typedef QPair<GraphId, GVSubGraph> GVSubGraphPair;

/// An object containing a libgraph graph and its associated nodes and edges
class GVGraph
{
  public:
    /*!
     * \brief Construct a Graphviz graph object
     * \param name The name of the graph, must be unique in the application
     */
    explicit GVGraph(const QString &name);
    ~GVGraph();

    GraphId addGraph(const QString &name);
    GraphId addGraph(const QString &name, GraphId subGraphId);
    void removeGraph(GraphId graphId);
    QList<GVSubGraphPair> gvSubGraphs() const;

    void setGraphAttr(const QString &attr, const QString &value, GraphId id = 0);

    /// Add and remove nodes
    NodeId addNode(const QString &name);
    NodeId addNode(const QString &name, GraphId subGraphId);
    QList<NodeId> addNodes(const QStringList &names);
    void removeNode(NodeId nodeId);
    void clearNodes();
    QList<GVNodePair> gvNodes() const;

    void setNodeAttribute(NodeId id, const QString &attr, const QString &value);

    /// Add and remove edges
    EdgeId addEdge(NodeId source, NodeId target, const QString &name);
    void removeEdge(EdgeId id);
    QList<GVEdgePair> gvEdges() const;

    void setEdgeAttribute(EdgeId id, const QString &attr, const QString &value);

    /// Set the font to use in all the labels
    void setFont(const QFont &font);

    QRectF boundingRect() const;

    void clear();

    void applyLayout();

  private:
    GraphId addGraph(const QString &name, Agraph_t *graph);
    NodeId addNode(const QString &name, Agraph_t *graph);

    void createGraph();
    void closeGraph();

    NodeId id(Agnode_t *node) const
    {
      return (NodeId)node;
    }

    EdgeId id(Agedge_t *edge) const
    {
      return (EdgeId)edge;
    }

    GraphId id(Agraph_t *graph) const
    {
      return (GraphId)graph;
    }

    Agnode_t *agNode(NodeId nodeId) const;
    Agedge_t *agEdge(EdgeId edgeId) const;
    Agraph_t *agGraph(GraphId graphId) const;

    QRectF boundingRectForAgraph(Agraph_t *graph) const;

    GVC_t *_context;
    Agraph_t *_graph;
    QFont _font;

    QString _name;

    // data
    QHash<Agraph_t *, GVSubGraph> _graphMap;
    QHash<Agedge_t *, GVEdge> _edgeMap;
    QHash<Agnode_t *, GVNode> _nodeMap;
};

}

#endif // GAMMARAY_GVGRAPH_H