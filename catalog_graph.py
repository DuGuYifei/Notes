# pip install pyvis markdown-it-py networkx
#
# Usage:
#   python -B .\catalog_graph.py . -o .\graph.html --open
#
#   # Typical (tuned) example:
#   python -B .\catalog_graph.py . -o .\graph.html --spring-iters 1400 --spring-k 0.12 --scale 14000 --font-size 1 --min-node-size 10 --max-node-size 30 --cluster-topk 30 --cluster-trim-q 0.0 --dim-alpha 0.2
#
#   # Better cluster boxes (less overlap / less "circle cloud"):
#   --no-hub --folder-weight 1.5
#
# Options (all -- flags):
#   -o, --out <path>                Output HTML path (default: graph.html)
#   --open                          Open output HTML after generation
#
#   --spring-iters <int>            spring_layout iterations (default: 1200)
#   --spring-k <float>              spring_layout k (0=auto). Smaller=tighter, larger=more spacing (default: 0.0)
#   --scale <float>                 Final coordinate scale (visual spacing) (default: 14000.0)
#
#   --folder-depth <int>            Folder backbone depth (0 disables) (default: 4)
#   --folder-weight <float>         Folder backbone edge weight (default: 6.0)
#   --no-hub                        Disable gravity hub (default: OFF)
#   --hub-weight <float>            Gravity hub edge weight (default: 0.12)
#
#   --font-size <int>               Label font size (default: 11)
#   --min-node-size <float>         Minimum node radius (default: 5.0)
#   --max-node-size <float>         Maximum node radius (default: 22.0)
#   --isolated-out <path>           Optional: write isolated md nodes to this txt file (default: "")
#
#   --cluster-topk <int>            Top-K candidate centers stored per cluster (UI shows top3) (default: 30)
#
#   --cluster-trim-q <float>        Trim quantile for cluster bbox (drop q on each tail).
#                                   Example: 0.05 => use 5%..95% nodes to compute bbox (default: 0.0)
#   --cluster-trim-min-n <int>      If cluster size < this, disable trimming (use full bbox) (default: 20)
#   --cluster-box-pad <float>       Extra padding around cluster bbox (canvas coords) (default: 140.0)
#
#   --dim-alpha <float>             Alpha for nodes outside keep-set when selecting a node (default: 0.20)
#
# Notes:
# - Produces ONLY graph.html (inline resources, no lib/)
# - Browser physics OFF; layout is computed offline by spring_layout (weighted)
# - Folder backbone + optional gravity hub to prevent "flung away" branches
# - Folder colors: up to N directory levels from root (default 4)
# - Clustering: md-only subgraph (Louvain if available else connected components)
#
# UI:
# - Cluster mode selector (4 modes):
#   1) Graph Cluster (algo)
#   2) Folder Cluster (depth=1)
#   3) Folder Cluster (depth=2)
#   4) Folder Cluster (depth=3)
# - Always draw cluster bbox outlines (very faint; outline only, no fill)
# - Hover node -> highlight its cluster outline + show "Possible Cluster Centers" panel (top-right)
# - Click/select node -> PIN that cluster outline (stays highlighted until deselect/click blank)
# - Click/select node -> dim all other nodes to --dim-alpha, BUT nodes in same (current-mode) cluster + neighbors stay unchanged
#
# Change from older versions:
# - NO Obsidian wikilink [[...]] parsing at all (only markdown links [text](href))

import argparse
import json
import math
import os
import re
from pathlib import Path
from urllib.parse import unquote

import networkx as nx
from markdown_it import MarkdownIt
from pyvis.network import Network

from catalog_ignore import IGNORE_FILES, IGNORE_DIRS

_MD = MarkdownIt("commonmark")

PALETTE = [
    "#60a5fa", "#34d399", "#f472b6", "#fbbf24", "#a78bfa",
    "#fb7185", "#22d3ee", "#4ade80", "#c084fc", "#f97316",
    "#93c5fd", "#86efac", "#fda4af", "#fde68a", "#ddd6fe",
]


def is_ignored_relpath(rel_path: Path) -> bool:
    return any(part in IGNORE_DIRS for part in rel_path.parts)


def iter_markdown_files(root: Path):
    for cur_root, dirs, files in os.walk(root):
        dirs[:] = [d for d in dirs if d not in IGNORE_DIRS]
        for fn in files:
            if fn in IGNORE_FILES:
                continue
            if not fn.lower().endswith(".md"):
                continue
            p = Path(cur_root) / fn
            try:
                rel = p.relative_to(root)
            except Exception:
                continue
            if is_ignored_relpath(rel):
                continue
            yield p


def build_md_index(root: Path):
    by_rel: dict[str, Path] = {}
    for p in iter_markdown_files(root):
        rel = p.relative_to(root).as_posix()
        by_rel[rel] = p
    return by_rel


def extract_links(text: str):
    """
    Extract ONLY Markdown-style links [text](href) using markdown-it.
    """
    out: list[str] = []
    tokens = _MD.parse(text)
    for t in tokens:
        if t.type != "inline" or not t.children:
            continue
        for c in t.children:
            if c.type == "link_open":
                href = c.attrGet("href")
                if not href:
                    continue
                href = href.strip()
                href = href.split("#", 1)[0]
                href = href.split("?", 1)[0]
                href = unquote(href)
                out.append(href)
    return out


def resolve_mdlink(root: Path, src: Path, target: str):
    t = target.strip().replace("\\", "/")

    # external links
    if re.match(r"^[a-zA-Z]+://", t):
        return None

    # absolute paths
    if re.match(r"^[a-zA-Z]:/", t) or t.startswith("/"):
        p = Path(t)
        return p if p.exists() else None

    # relative to current file
    p1 = (src.parent / t).resolve()
    if p1.exists():
        return p1

    # relative to root
    p2 = (root / t).resolve()
    if p2.exists():
        return p2

    # try adding .md
    if not t.lower().endswith(".md"):
        p3 = (src.parent / (t + ".md")).resolve()
        if p3.exists():
            return p3
        p4 = (root / (t + ".md")).resolve()
        if p4.exists():
            return p4

    return None


def should_include_nonmd(p: Path, root: Path) -> bool:
    if p.name in IGNORE_FILES:
        return False
    try:
        rel = p.resolve().relative_to(root)
        if is_ignored_relpath(rel):
            return False
    except Exception:
        pass
    return True


def folder_key(rel_posix: str, depth: int = 4) -> str:
    parts = rel_posix.split("/")
    if len(parts) <= 1:
        return "ROOT"
    dir_parts = parts[:-1][:depth]
    return "/".join(dir_parts) if dir_parts else "ROOT"


def normalize_and_scale(pos: dict[str, tuple[float, float]], scale: float) -> dict[str, tuple[float, float]]:
    if not pos:
        return pos

    xs = [x for x, _ in pos.values()]
    ys = [y for _, y in pos.values()]
    cx = sum(xs) / len(xs)
    cy = sum(ys) / len(ys)

    centered = {nid: (x - cx, y - cy) for nid, (x, y) in pos.items()}
    rmax = 0.0
    for x, y in centered.values():
        rmax = max(rmax, math.hypot(x, y))
    if rmax <= 1e-9:
        rmax = 1.0

    return {nid: (x / rmax * scale, y / rmax * scale) for nid, (x, y) in centered.items()}


# ---------------------------
# Layout stabilizers
# ---------------------------

def folder_node_id(folder_rel_posix: str) -> str:
    return f"__FOLDER__:{folder_rel_posix}"


def add_folder_backbone(G: nx.Graph, md_rels: list[str], depth: int, w_folder: float):
    """
    Add folder nodes and weighted edges:
      file -> folder (deepest within depth)
      folder -> parent folder chain up to ROOT
    """
    root_folder = "ROOT"
    G.add_node(folder_node_id(root_folder))

    created_folder: set[str] = {root_folder}

    def ensure_folder_chain(parts: list[str]):
        prev = root_folder
        for i in range(1, len(parts) + 1):
            now = "/".join(parts[:i])
            if now not in created_folder:
                G.add_node(folder_node_id(now))
                created_folder.add(now)
            G.add_edge(folder_node_id(prev), folder_node_id(now), weight=w_folder)
            prev = now

    for rel in md_rels:
        folder_parts = rel.split("/")[:-1]
        folder_parts = folder_parts[:depth] if depth > 0 else []

        if folder_parts:
            ensure_folder_chain(folder_parts)
            leaf_folder = "/".join(folder_parts)
        else:
            leaf_folder = root_folder

        G.add_node(folder_node_id(leaf_folder))
        G.add_edge(rel, folder_node_id(leaf_folder), weight=w_folder)


def add_gravity_hub(G: nx.Graph, md_rels: list[str], w_hub: float) -> str:
    """
    Add an invisible hub connected to all markdown nodes with small weight.
    """
    hub = "__CENTER__"
    G.add_node(hub)
    for n in md_rels:
        G.add_edge(hub, n, weight=w_hub)
    return hub


def compute_layout_spring(G: nx.Graph, iters: int, k: float | None, scale: float) -> dict[str, tuple[float, float]]:
    raw = nx.spring_layout(G, seed=42, iterations=iters, k=k, weight="weight")
    pos = {nid: (float(x), float(y)) for nid, (x, y) in raw.items()}
    return normalize_and_scale(pos, scale)


# ---------------------------
# Clustering (md-only)
# ---------------------------

def compute_md_clusters(md_subgraph: nx.Graph, seed: int = 42) -> dict[str, int]:
    """
    Return mapping node->cluster_id on md-only subgraph.
    Prefer Louvain if available; fallback to connected components.
    """
    try:
        from networkx.algorithms.community import louvain_communities  # type: ignore
        comms = louvain_communities(md_subgraph, seed=seed, weight="weight", resolution=1.0)
        node_to_c: dict[str, int] = {}
        for i, comm in enumerate(comms):
            for n in comm:
                node_to_c[n] = i
        return node_to_c
    except Exception:
        node_to_c: dict[str, int] = {}
        for i, comp in enumerate(nx.connected_components(md_subgraph)):
            for n in comp:
                node_to_c[n] = i
        return node_to_c


def clusters_from_node_to_c(node_to_c: dict[str, int]) -> dict[int, list[str]]:
    clusters: dict[int, list[str]] = {}
    for n, cid in node_to_c.items():
        clusters.setdefault(cid, []).append(n)
    return clusters


def compute_cluster_topk(md_subgraph: nx.Graph, clusters: dict[int, list[str]], topk: int) -> dict[int, list[tuple[str, int]]]:
    """
    For each cluster, compute TopK nodes by intra-cluster degree (within md_subgraph).
    """
    out: dict[int, list[tuple[str, int]]] = {}
    for cid, nodes in clusters.items():
        H = md_subgraph.subgraph(nodes)
        items = [(n, int(H.degree[n])) for n in nodes]
        items.sort(key=lambda x: (-x[1], x[0]))
        out[cid] = items[: max(1, int(topk))]
    return out


def folder_node_to_cluster(md_rels: list[str], depth: int) -> dict[str, int]:
    """
    Deterministic folder clustering for md nodes:
      cluster key = folder_key(rel, depth)
    """
    key_to_id: dict[str, int] = {}
    node_to_c: dict[str, int] = {}
    next_id = 0
    for rel in md_rels:
        k = folder_key(rel, depth=depth)
        if k not in key_to_id:
            key_to_id[k] = next_id
            next_id += 1
        node_to_c[rel] = key_to_id[k]
    return node_to_c


# ---------------------------
# HTML injection
# ---------------------------

def inject_cluster_ui_js(
    html: str,
    payload_json: str,
    trim_q: float,
    trim_min_n: int,
    box_pad: float,
    dim_alpha: float,
) -> str:
    m = re.search(r"new\s+vis\.Network\s*\(\s*container\s*,\s*data\s*,\s*options\s*\)\s*;", html)
    if not m:
        m = re.search(r"new\s+vis\.Network\s*\(", html)
        if not m:
            return html
        insert_pos = m.end()
    else:
        insert_pos = m.end()

    js = r"""
// --- Cluster UI: 4 modes (algo + folder depth 1/2/3) ---
(function () {
  var PAY = %PAYLOAD_JSON%;
  var TRIM_Q = %TRIM_Q%;
  var TRIM_MIN_N = %TRIM_MIN_N%;
  var BOX_PAD = %BOX_PAD%;
  var DIM_ALPHA = %DIM_ALPHA%;

  if (typeof network === "undefined" || typeof nodes === "undefined") {
    console.error("[cluster overlay] network/nodes not found.");
    return;
  }

  // ---------- UI: mode selector ----------
  var modeBox = document.createElement("div");
  modeBox.id = "clusterModeBox";
  modeBox.style.position = "fixed";
  modeBox.style.left = "12px";
  modeBox.style.top = "12px";
  modeBox.style.zIndex = "10000";
  modeBox.style.padding = "8px 10px";
  modeBox.style.borderRadius = "10px";
  modeBox.style.background = "rgba(2, 6, 23, 0.72)";
  modeBox.style.border = "1px solid rgba(148, 163, 184, 0.22)";
  modeBox.style.color = "#e5e7eb";
  modeBox.style.font = "12px/1.35 ui-sans-serif, system-ui, -apple-system, Segoe UI, Roboto, Helvetica, Arial";
  modeBox.style.backdropFilter = "blur(6px)";

  var label = document.createElement("div");
  label.textContent = "Cluster Mode";
  label.style.opacity = "0.85";
  label.style.marginBottom = "6px";
  modeBox.appendChild(label);

  var sel = document.createElement("select");
  sel.style.width = "240px";
  sel.style.background = "rgba(15, 23, 42, 0.85)";
  sel.style.color = "#e5e7eb";
  sel.style.border = "1px solid rgba(148, 163, 184, 0.25)";
  sel.style.borderRadius = "8px";
  sel.style.padding = "6px 8px";
  sel.style.outline = "none";

  function addOpt(val, text) {
    var o = document.createElement("option");
    o.value = val;
    o.textContent = text;
    sel.appendChild(o);
  }

  // modes defined in payload
  addOpt("algo", "Graph Cluster (Algo)");
  addOpt("folder1", "Folder Cluster (depth=1)");
  addOpt("folder2", "Folder Cluster (depth=2)");
  addOpt("folder3", "Folder Cluster (depth=3)");

  modeBox.appendChild(sel);
  document.body.appendChild(modeBox);

  // ---------- Panel (top-right) ----------
  var panel = document.createElement("div");
  panel.id = "clusterPanel";
  panel.style.position = "fixed";
  panel.style.top = "12px";
  panel.style.right = "12px";
  panel.style.zIndex = "9999";
  panel.style.maxWidth = "420px";
  panel.style.padding = "10px 12px";
  panel.style.borderRadius = "10px";
  panel.style.background = "rgba(2, 6, 23, 0.72)";
  panel.style.border = "1px solid rgba(148, 163, 184, 0.22)";
  panel.style.color = "#e5e7eb";
  panel.style.font = "12px/1.35 ui-sans-serif, system-ui, -apple-system, Segoe UI, Roboto, Helvetica, Arial";
  panel.style.backdropFilter = "blur(6px)";
  panel.style.pointerEvents = "none";
  panel.innerHTML = "<div style='opacity:.85'>Hover or select a node to see cluster centers</div>";
  document.body.appendChild(panel);

  function escapeHtml(s) {
    return String(s).replace(/&/g,"&amp;").replace(/</g,"&lt;").replace(/>/g,"&gt;")
                    .replace(/"/g,"&quot;").replace(/'/g,"&#039;");
  }

  // Cache original node styles (for restore)
  var allNodesObj = nodes.get({ returnType: "Object" });
  var original = {};
  for (var id in allNodesObj) {
    if (!allNodesObj.hasOwnProperty(id)) continue;
    original[id] = { color: allNodesObj[id].color, font: allNodesObj[id].font };
  }

  // ---------- Mode state ----------
  var currentMode = "algo";
  var CL = PAY.modes[currentMode]; // {clusters: {cid: {nodes, top}}}

  var nodeToCluster = {};
  function rebuildNodeToCluster() {
    nodeToCluster = {};
    var clusters = CL.clusters || {};
    for (var cid in clusters) {
      if (!clusters.hasOwnProperty(cid)) continue;
      var arr = clusters[cid].nodes || [];
      for (var i = 0; i < arr.length; i++) nodeToCluster[arr[i]] = cid;
    }
  }

  // Quantile helper
  function quantile(sortedArr, q) {
    if (!sortedArr || sortedArr.length === 0) return 0;
    var idx = Math.floor((sortedArr.length - 1) * q);
    if (idx < 0) idx = 0;
    if (idx >= sortedArr.length) idx = sortedArr.length - 1;
    return sortedArr[idx];
  }

  // Compute trimmed bbox per cluster (canvas coords)
  var clusterBBoxes = {}; // cid -> {minX,minY,maxX,maxY}
  function computeBBoxes() {
    clusterBBoxes = {};
    var clusters = CL.clusters || {};

    for (var cid in clusters) {
      if (!clusters.hasOwnProperty(cid)) continue;
      var nodesIn = clusters[cid].nodes || [];
      if (nodesIn.length === 0) continue;

      var posMap = network.getPositions(nodesIn);
      var xs = [];
      var ys = [];

      for (var i = 0; i < nodesIn.length; i++) {
        var nid = nodesIn[i];
        var p = posMap[nid];
        if (!p) continue;
        xs.push(p.x);
        ys.push(p.y);
      }
      if (xs.length === 0) continue;

      xs.sort(function(a,b){ return a-b; });
      ys.sort(function(a,b){ return a-b; });

      var q = (xs.length >= TRIM_MIN_N) ? TRIM_Q : 0.0;

      var minX = quantile(xs, q);
      var maxX = quantile(xs, 1.0 - q);
      var minY = quantile(ys, q);
      var maxY = quantile(ys, 1.0 - q);

      if (maxX < minX) { var t = minX; minX = maxX; maxX = t; }
      if (maxY < minY) { var u = minY; minY = maxY; maxY = u; }

      clusterBBoxes[cid] = {
        minX: minX - BOX_PAD, minY: minY - BOX_PAD,
        maxX: maxX + BOX_PAD, maxY: maxY + BOX_PAD
      };
    }
  }

  // hover (temporary) vs pinned (select) cluster
  var hoverCluster = null;
  var pinnedCluster = null;

  function activeCluster() {
    return pinnedCluster != null ? pinnedCluster : hoverCluster;
  }

  function updatePanel(cid) {
    if (cid == null) {
      panel.innerHTML = "<div style='opacity:.85'>Hover or select a node to see cluster centers</div>";
      return;
    }
    var clusters = CL.clusters || {};
    var c = clusters[cid];
    if (!c) return;

    var lines = [];
    lines.push("<div style='font-size:13px; font-weight:600; margin-bottom:6px;'>Possible Cluster Centers:</div>");

    var top = c.top || [];
    for (var i = 0; i < Math.min(top.length, 3); i++) {
      var row = top[i];
      var label = row.label || row.id;
      lines.push(
        "<div style='white-space:nowrap; overflow:hidden; text-overflow:ellipsis; opacity:.95;'>" +
        escapeHtml(label) + ",</div>"
      );
    }
    panel.innerHTML = lines.join("");
  }

  // ---- Node dimming helpers ----
  function parseHexToRgb(hex) {
    var m = /^#([0-9a-fA-F]{6})$/.exec(hex);
    if (!m) return null;
    var s = m[1];
    return { r: parseInt(s.slice(0,2), 16), g: parseInt(s.slice(2,4), 16), b: parseInt(s.slice(4,6), 16) };
  }

  function rgbaFromColorString(colorStr, alpha) {
    if (!colorStr) return "rgba(226,232,240," + alpha + ")";
    var s = String(colorStr).trim();

    var mrgba = /^rgba\(\s*([0-9.]+)\s*,\s*([0-9.]+)\s*,\s*([0-9.]+)\s*,\s*([0-9.]+)\s*\)$/.exec(s);
    if (mrgba) return "rgba(" + mrgba[1] + "," + mrgba[2] + "," + mrgba[3] + "," + alpha + ")";

    var mrgb = /^rgb\(\s*([0-9.]+)\s*,\s*([0-9.]+)\s*,\s*([0-9.]+)\s*\)$/.exec(s);
    if (mrgb) return "rgba(" + mrgb[1] + "," + mrgb[2] + "," + mrgb[3] + "," + alpha + ")";

    var rgb = parseHexToRgb(s);
    if (rgb) return "rgba(" + rgb.r + "," + rgb.g + "," + rgb.b + "," + alpha + ")";

    return "rgba(226,232,240," + alpha + ")";
  }

  function dimOutsideKeep(keepSet) {
    var all = nodes.get({ returnType: "Object" });
    var upd = [];

    for (var id in all) {
      if (!all.hasOwnProperty(id)) continue;

      if (keepSet && keepSet[id]) {
        if (original[id]) upd.push({ id: id, color: original[id].color, font: original[id].font });
        continue;
      }

      var orig = original[id] || {};
      var origColor = (orig.color || {});
      var bg = origColor.background || "#94a3b8";
      var bd = origColor.border || bg;

      upd.push({
        id: id,
        color: { background: rgbaFromColorString(bg, DIM_ALPHA), border: rgbaFromColorString(bd, DIM_ALPHA) },
        font: { color: "rgba(229,231,235," + DIM_ALPHA + ")" }
      });
    }
    nodes.update(upd);
  }

  function restoreAllNodes() {
    var all = nodes.get({ returnType: "Object" });
    var upd = [];
    for (var id in all) {
      if (!all.hasOwnProperty(id)) continue;
      if (!original[id]) continue;
      upd.push({ id: id, color: original[id].color, font: original[id].font });
    }
    nodes.update(upd);
  }

  // ---- Draw bbox outlines (YOUR settings) ----
  network.on("afterDrawing", function (ctx) {
    var ac = activeCluster();
    for (var cid in clusterBBoxes) {
      if (!clusterBBoxes.hasOwnProperty(cid)) continue;
      var b = clusterBBoxes[cid];
      var isActive = (ac != null && String(cid) === String(ac));

      ctx.save();
      ctx.beginPath();
      ctx.rect(b.minX, b.minY, b.maxX - b.minX, b.maxY - b.minY);

      // YOUR modified width + color
      ctx.lineWidth = isActive ? 8.0 : 1.0;
      ctx.strokeStyle = isActive ? "rgba(220, 20, 60, 0.38)" : "rgba(226, 232, 240, 0.05)";
      ctx.stroke();
      ctx.restore();
    }
  });

  // Hover node -> only if not pinned
  network.on("hoverNode", function (params) {
    if (pinnedCluster != null) return;
    var nid = params.node;
    var cid = nodeToCluster[nid];
    hoverCluster = (typeof cid === "undefined") ? null : cid;
    updatePanel(hoverCluster);
    network.redraw();
  });

  network.on("blurNode", function () {
    if (pinnedCluster != null) return;
    hoverCluster = null;
    updatePanel(null);
    network.redraw();
  });

  // Select node -> pin cluster + dim outside keep-set (cluster depends on current mode)
  network.on("selectNode", function (params) {
    var nid = params.nodes && params.nodes[0];
    if (!nid) return;

    var cid = nodeToCluster[nid];
    if (typeof cid === "undefined") {
      pinnedCluster = null;
      updatePanel(null);
      restoreAllNodes();
      network.redraw();
      return;
    }

    pinnedCluster = cid;
    updatePanel(cid);

    var keep = {};
    keep[nid] = true;

    var neighbors = network.getConnectedNodes(nid) || [];
    for (var i = 0; i < neighbors.length; i++) keep[neighbors[i]] = true;

    var clusters = CL.clusters || {};
    var c = clusters[cid];
    var cnodes = (c && c.nodes) ? c.nodes : [];
    for (var j = 0; j < cnodes.length; j++) keep[cnodes[j]] = true;

    dimOutsideKeep(keep);
    network.redraw();
  });

  // Click blank / deselect -> unpin + restore
  network.on("deselectNode", function () {
    pinnedCluster = null;
    if (hoverCluster != null) updatePanel(hoverCluster);
    else updatePanel(null);

    restoreAllNodes();
    network.redraw();
  });

  function recomputeSoon() {
    setTimeout(function () {
      try { computeBBoxes(); network.redraw(); } catch (e) {}
    }, 10);
  }
  network.on("stabilizationIterationsDone", recomputeSoon);
  network.on("dragEnd", recomputeSoon);
  network.on("zoom", recomputeSoon);

  function applyMode(newMode) {
    if (!PAY.modes[newMode]) return;

    // Clear selection + pinned effects
    try { network.unselectAll(); } catch (e) {}
    pinnedCluster = null;
    hoverCluster = null;
    restoreAllNodes();
    updatePanel(null);

    currentMode = newMode;
    CL = PAY.modes[currentMode];

    rebuildNodeToCluster();
    computeBBoxes();
    network.redraw();
  }

  sel.addEventListener("change", function () {
    applyMode(sel.value);
  });

  // init
  rebuildNodeToCluster();
  computeBBoxes();
})();
"""
    js = js.replace("%PAYLOAD_JSON%", payload_json)
    js = js.replace("%TRIM_Q%", json.dumps(float(trim_q)))
    js = js.replace("%TRIM_MIN_N%", json.dumps(int(trim_min_n)))
    js = js.replace("%BOX_PAD%", json.dumps(float(box_pad)))
    js = js.replace("%DIM_ALPHA%", json.dumps(float(dim_alpha)))

    return html[:insert_pos] + "\n" + js + "\n" + html[insert_pos:]


def main():
    ap = argparse.ArgumentParser(description="Generate a single-file graph.html (offline spring layout, stabilized).")
    ap.add_argument("root", help=r"Root folder (e.g., E:\Notes)")
    ap.add_argument("-o", "--out", default="graph.html", help="Output HTML path")
    ap.add_argument("--open", action="store_true", help="Open output HTML after generation")

    # Layout controls (spring only)
    ap.add_argument("--spring-iters", type=int, default=1200, help="spring_layout iterations (higher=better, slower)")
    ap.add_argument(
        "--spring-k", type=float, default=0.0,
        help="spring_layout k (0=auto). Smaller -> tighter; larger -> more spacing"
    )
    ap.add_argument("--scale", type=float, default=14000.0, help="Final coordinate scale (visual spacing)")

    # Stabilizers
    ap.add_argument("--folder-depth", type=int, default=4, help="Folder backbone depth (0 disables)")
    ap.add_argument("--folder-weight", type=float, default=6.0, help="Folder backbone edge weight")
    ap.add_argument("--no-hub", action="store_true", help="Disable gravity hub")
    ap.add_argument("--hub-weight", type=float, default=0.12, help="Gravity hub edge weight (smaller = weaker pull)")

    # Rendering controls
    ap.add_argument("--font-size", type=int, default=11, help="Label font size")
    ap.add_argument("--min-node-size", type=float, default=5.0, help="Minimum node radius")
    ap.add_argument("--max-node-size", type=float, default=22.0, help="Maximum node radius (caps hubs)")
    ap.add_argument("--isolated-out", default="", help="Optional: write isolated md nodes to this txt file")

    # Cluster display (centers)
    ap.add_argument("--cluster-topk", type=int, default=30, help="Top-K candidate centers stored per cluster (UI shows top3)")

    # Cluster bbox trimming controls
    ap.add_argument(
        "--cluster-trim-q",
        type=float,
        default=0.0,
        help="Trim quantile for bbox (drop q on each tail). Example 0.05 => use 5%%..95%%."
    )
    ap.add_argument(
        "--cluster-trim-min-n",
        type=int,
        default=20,
        help="If cluster size < this, disable trimming (use full bbox)."
    )
    ap.add_argument(
        "--cluster-box-pad",
        type=float,
        default=140.0,
        help="Extra padding added around cluster bbox (in canvas coordinates)."
    )

    # Dimming controls (on select)
    ap.add_argument(
        "--dim-alpha",
        type=float,
        default=0.20,
        help="Alpha for nodes outside keep-set when selecting a node."
    )

    args = ap.parse_args()

    root = Path(args.root).expanduser().resolve()
    if not root.exists() or not root.is_dir():
        raise SystemExit(f"Root folder not found or not a directory: {root}")

    by_rel = build_md_index(root)
    if not by_rel:
        raise SystemExit("No markdown files found under root (after ignores).")

    color_depth = max(1, int(args.folder_depth)) if int(args.folder_depth) > 0 else 4
    folder_groups = sorted({folder_key(rel, depth=color_depth) for rel in by_rel.keys()})
    folder_to_color = {f: PALETTE[i % len(PALETTE)] for i, f in enumerate(folder_groups)}

    # Build graph
    G = nx.Graph()
    degree_content: dict[str, int] = {}  # counts content edges only (md-md + md-nonmd), not stabilizers

    def bump_degree(a: str, b: str):
        degree_content[a] = degree_content.get(a, 0) + 1
        degree_content[b] = degree_content.get(b, 0) + 1

    for rel in by_rel.keys():
        G.add_node(rel)
        degree_content.setdefault(rel, 0)

    # Content edges (weight=1) — ONLY markdown links are parsed
    for rel, src in by_rel.items():
        text = src.read_text(encoding="utf-8", errors="ignore")
        for target in extract_links(text):
            resolved = resolve_mdlink(root, src, target)
            if resolved is None:
                continue

            try:
                rel_target = resolved.resolve().relative_to(root)
                if is_ignored_relpath(rel_target):
                    continue
            except Exception:
                pass

            if resolved.suffix.lower() == ".md":
                try:
                    tid = resolved.resolve().relative_to(root).as_posix()
                except Exception:
                    continue
                if tid in by_rel and tid != rel:
                    G.add_edge(rel, tid, weight=1.0)
                    bump_degree(rel, tid)
                continue

            # non-md (optional)
            if not should_include_nonmd(resolved, root):
                continue

            nid = str(resolved.resolve())
            G.add_node(nid)
            G.add_edge(rel, nid, weight=1.0)
            bump_degree(rel, nid)

    # Stabilizers: folder backbone + optional hub
    md_rels = list(by_rel.keys())
    if int(args.folder_depth) > 0 and float(args.folder_weight) > 0:
        add_folder_backbone(G, md_rels, depth=int(args.folder_depth), w_folder=float(args.folder_weight))

    hub_id = None
    if not args.no_hub and float(args.hub_weight) > 0:
        hub_id = add_gravity_hub(G, md_rels, w_hub=float(args.hub_weight))

    # Layout (weighted spring)
    scale = float(args.scale)
    k = None if float(args.spring_k) <= 0 else float(args.spring_k)
    pos = compute_layout_spring(G, iters=max(50, int(args.spring_iters)), k=k, scale=scale)

    # Clustering on md-only subgraph
    md_sub = G.subgraph(md_rels).copy()

    # mode: algo
    algo_node_to_c = compute_md_clusters(md_sub, seed=42)
    algo_clusters = clusters_from_node_to_c(algo_node_to_c)
    algo_top = compute_cluster_topk(md_sub, algo_clusters, topk=int(args.cluster_topk))

    # mode: folder depth 1/2/3
    f1_node_to_c = folder_node_to_cluster(md_rels, depth=1)
    f2_node_to_c = folder_node_to_cluster(md_rels, depth=2)
    f3_node_to_c = folder_node_to_cluster(md_rels, depth=3)

    f1_clusters = clusters_from_node_to_c(f1_node_to_c)
    f2_clusters = clusters_from_node_to_c(f2_node_to_c)
    f3_clusters = clusters_from_node_to_c(f3_node_to_c)

    f1_top = compute_cluster_topk(md_sub, f1_clusters, topk=int(args.cluster_topk))
    f2_top = compute_cluster_topk(md_sub, f2_clusters, topk=int(args.cluster_topk))
    f3_top = compute_cluster_topk(md_sub, f3_clusters, topk=int(args.cluster_topk))

    def build_mode_payload(clusters: dict[int, list[str]], topmap: dict[int, list[tuple[str, int]]]) -> dict:
        clusters_payload: dict[str, dict] = {}
        for cid, nodes_in in clusters.items():
            nodes_in_sorted = sorted(nodes_in)
            top_rows = []
            for nid, deg_in in topmap.get(cid, []):
                label = by_rel[nid].stem if nid in by_rel else nid
                top_rows.append({"id": nid, "label": label, "deg": int(deg_in)})
            clusters_payload[str(cid)] = {"nodes": nodes_in_sorted, "top": top_rows}
        return {"clusters": clusters_payload}

    payload = {
        "modes": {
            "algo": build_mode_payload(algo_clusters, algo_top),
            "folder1": build_mode_payload(f1_clusters, f1_top),
            "folder2": build_mode_payload(f2_clusters, f2_top),
            "folder3": build_mode_payload(f3_clusters, f3_top),
        }
    }
    payload_json = json.dumps(payload, ensure_ascii=False)

    # PyVis rendering (single-file inline)
    net = Network(
        height="100vh",
        width="100%",
        bgcolor="#0b0f14",
        font_color="#cbd5e1",
        directed=False,
        cdn_resources="in_line",
    )

    net.set_options(r"""
{
  "physics": { "enabled": false },
  "interaction": { "hover": true, "navigationButtons": false, "keyboard": false },
  "edges": { "color": { "color": "rgba(203,213,225,0.16)" }, "smooth": false }
}
""")

    font_size = max(6, int(args.font_size))
    min_size = float(args.min_node_size)
    max_size = float(args.max_node_size)

    def node_size(deg: int) -> float:
        s = min_size + min(deg, 30) * 0.7
        return max(min_size, min(max_size, s))

    added: set[str] = set()

    def add_node(node_id: str, label: str, title: str, shape: str, color_hex: str, size: float | None = None):
        if node_id in added:
            return
        x, y = pos.get(node_id, (0.0, 0.0))
        if size is None:
            deg = int(G.degree[node_id])
            size = node_size(deg)

        net.add_node(
            node_id,
            label=label,
            title=title,
            shape=shape,
            size=size,
            color={"background": color_hex, "border": color_hex},
            font={"color": "#e5e7eb", "size": font_size},
            x=x,
            y=y,
            fixed=True,
            physics=False,
        )
        added.add(node_id)

    for node_id in G.nodes():
        if hub_id is not None and node_id == hub_id:
            continue

        if node_id.startswith("__FOLDER__:"):
            add_node(node_id, "", node_id, "dot", "#334155", size=2.6)
            continue

        if node_id in by_rel:
            p = by_rel[node_id]
            fk = folder_key(node_id, depth=color_depth)
            add_node(node_id, p.stem, node_id, "dot", folder_to_color.get(fk, PALETTE[0]))
        else:
            add_node(node_id, Path(node_id).name, node_id, "box", "#64748b")

    for a, b in G.edges():
        if hub_id is not None and (a == hub_id or b == hub_id):
            continue
        net.add_edge(a, b)

    out_path = Path(args.out).expanduser().resolve()

    html = net.generate_html(notebook=False)
    html = inject_cluster_ui_js(
        html=html,
        payload_json=payload_json,
        trim_q=max(0.0, min(0.49, float(args.cluster_trim_q))),
        trim_min_n=max(0, int(args.cluster_trim_min_n)),
        box_pad=float(args.cluster_box_pad),
        dim_alpha=max(0.0, min(1.0, float(args.dim_alpha))),
    )
    out_path.write_text(html, encoding="utf-8", errors="strict")

    isolated_md = [nid for nid in by_rel.keys() if degree_content.get(nid, 0) == 0]

    print(f"OK: wrote {out_path}")
    print(f"Stats: md_nodes={len(by_rel)} total_nodes={G.number_of_nodes()} edges={G.number_of_edges()}")
    print("Layout used: spring_layout (weighted)")
    print(f"Folder backbone: depth={int(args.folder_depth)} weight={float(args.folder_weight)}")
    print(f"Gravity hub: {'OFF' if args.no_hub else 'ON'} (weight={float(args.hub_weight)})")
    print(f"Clusters (md-only algo): {len(algo_clusters)}  (algo: Louvain if available else CC)")
    print(f"Folder clusters: depth1={len(f1_clusters)} depth2={len(f2_clusters)} depth3={len(f3_clusters)}")
    print(f"Cluster bbox trim: q={float(args.cluster_trim_q)} (each tail), min_n={int(args.cluster_trim_min_n)}, pad={float(args.cluster_box_pad)}")
    print(f"Select dim alpha: {float(args.dim_alpha)}")
    print(f"Isolated markdown nodes: {len(isolated_md)}")
    for nid in sorted(isolated_md):
        print(nid)

    if args.isolated_out:
        iso_path = Path(args.isolated_out).expanduser().resolve()
        iso_path.write_text("\n".join(sorted(isolated_md)), encoding="utf-8")
        print(f"Wrote isolated list to: {iso_path}")

    if args.open:
        try:
            import webbrowser
            webbrowser.open(out_path.as_uri())
        except Exception:
            pass


if __name__ == "__main__":
    main()