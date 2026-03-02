# pip install pyvis markdown-it-py networkx
#
# Usage:
#   python -B .\catalog_graph.py . -o .\graph.html --open
#   python -B .\catalog_graph.py . -o .\graph.html --spring-iters 1400 --spring-k 0.12 --scale 14000 --font-size 1 --min-node-size 10 --max-node-size 30
#
# Notes:
# - Produces ONLY graph.html (inline resources, no lib/)
# - Browser physics OFF; layout is computed offline by spring_layout (weighted)
# - Folder backbone + optional gravity hub to prevent "flung away" branches
# - Folder colors: up to N directory levels from root (default 4)
# - Hover highlight neighbors (dim others)

import argparse
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

WIKILINK_RE = re.compile(r"\[\[([^\]\|#]+)(?:#[^\]\|]+)?(?:\|[^\]]+)?\]\]")

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
    by_stem: dict[str, list[Path]] = {}
    for p in iter_markdown_files(root):
        rel = p.relative_to(root).as_posix()
        by_rel[rel] = p
        by_stem.setdefault(p.stem, []).append(p)
    return by_rel, by_stem


def extract_links(text: str):
    out: list[tuple[str, str]] = []

    # Obsidian wiki links
    for m in WIKILINK_RE.finditer(text):
        out.append(("wiki", m.group(1).strip()))

    # Markdown links
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
                out.append(("md", href))

    return out


def resolve_wikilink(src: Path, target: str, by_stem: dict[str, list[Path]]):
    key = target.strip().replace("\\", "/").split("/")[-1]
    cands = by_stem.get(key)
    if not cands:
        return None
    if len(cands) == 1:
        return cands[0]

    # pick the candidate that shares the longest common prefix path with src
    src_parts = src.parts

    def score(p: Path):
        common = 0
        for a, b in zip(src_parts, p.parts):
            if a == b:
                common += 1
            else:
                break
        return common

    return sorted(cands, key=score, reverse=True)[0]


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


def inject_hover_highlight_js(html: str) -> str:
    marker = "var network = new vis.Network(container, data, options);"
    idx = html.find(marker)
    if idx == -1:
        return html
    insert_pos = idx + len(marker)

    js = r"""
// --- Hover highlight neighbors (injected) ---
(function () {
  var allNodes = nodes.get({ returnType: "Object" });

  var original = {};
  for (var id in allNodes) {
    if (!allNodes.hasOwnProperty(id)) continue;
    original[id] = { color: allNodes[id].color, font: allNodes[id].font };
  }

  function dimAll() {
    allNodes = nodes.get({ returnType: "Object" });
    var update = [];
    for (var id in allNodes) {
      if (!allNodes.hasOwnProperty(id)) continue;
      update.push({
        id: id,
        color: { background: "#233044", border: "#233044" },
        font: { color: "#6b7280" }
      });
    }
    nodes.update(update);
  }

  function restoreAll() {
    allNodes = nodes.get({ returnType: "Object" });
    var update = [];
    for (var id in allNodes) {
      if (!allNodes.hasOwnProperty(id)) continue;
      if (!original[id]) continue;
      update.push({ id: id, color: original[id].color, font: original[id].font });
    }
    nodes.update(update);
  }

  network.on("hoverNode", function (params) {
    dimAll();
    var nodeId = params.node;
    var neighbors = network.getConnectedNodes(nodeId);
    var keep = [nodeId].concat(neighbors);

    var update = [];
    for (var i = 0; i < keep.length; i++) {
      var id = keep[i];
      if (!original[id]) continue;
      update.push({ id: id, color: original[id].color, font: original[id].font });
    }
    nodes.update(update);
  });

  network.on("blurNode", function () { restoreAll(); });
})();
"""
    return html[:insert_pos] + "\n" + js + "\n" + html[insert_pos:]

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
    This prevents sparse subgraphs from flying away and makes the overall shape rounder.
    """
    root_folder = "ROOT"
    root_id = folder_node_id(root_folder)
    G.add_node(root_id)

    # ensure parent chains exist once
    created_folder: set[str] = {root_folder}

    def ensure_folder_chain(parts: list[str]):
        prev = root_folder
        for i in range(1, len(parts) + 1):
            now = "/".join(parts[:i])
            if now not in created_folder:
                G.add_node(folder_node_id(now))
                created_folder.add(now)
            # connect prev -> now
            G.add_edge(folder_node_id(prev), folder_node_id(now), weight=w_folder)
            prev = now

    for rel in md_rels:
        folder_parts = rel.split("/")[:-1]  # directory parts
        folder_parts = folder_parts[:depth] if depth > 0 else []

        # build chain from ROOT
        if folder_parts:
            ensure_folder_chain(folder_parts)
            leaf_folder = "/".join(folder_parts)
        else:
            leaf_folder = root_folder

        # connect file to leaf folder
        G.add_node(folder_node_id(leaf_folder))
        G.add_edge(rel, folder_node_id(leaf_folder), weight=w_folder)


def add_gravity_hub(G: nx.Graph, md_rels: list[str], w_hub: float) -> str:
    """
    Add an invisible hub connected to all markdown nodes with small weight.
    This gently pulls the layout into a single compact "cloud".
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


def main():
    ap = argparse.ArgumentParser(description="Generate a single-file graph.html (offline spring layout, stabilized).")
    ap.add_argument("root", help=r"Root folder (e.g., E:\Notes)")
    ap.add_argument("-o", "--out", default="graph.html", help="Output HTML path")
    ap.add_argument("--open", action="store_true", help="Open output HTML after generation")

    # Layout controls (spring only)
    ap.add_argument("--spring-iters", type=int, default=1200, help="spring_layout iterations (higher=better, slower)")
    ap.add_argument("--spring-k", type=float, default=0.0,
                    help="spring_layout k (0=auto). Smaller -> tighter; larger -> more spacing")
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

    args = ap.parse_args()

    root = Path(args.root).expanduser().resolve()
    if not root.exists() or not root.is_dir():
        raise SystemExit(f"Root folder not found or not a directory: {root}")

    by_rel, by_stem = build_md_index(root)
    if not by_rel:
        raise SystemExit("No markdown files found under root (after ignores).")

    color_depth = max(1, int(args.folder_depth)) if int(args.folder_depth) > 0 else 4
    folder_groups = sorted({folder_key(rel, depth=color_depth) for rel in by_rel.keys()})
    folder_to_color = {f: PALETTE[i % len(PALETTE)] for i, f in enumerate(folder_groups)}

    # Build graph
    G = nx.Graph()
    degree: dict[str, int] = {}

    def bump_degree(a: str, b: str):
        degree[a] = degree.get(a, 0) + 1
        degree[b] = degree.get(b, 0) + 1

    for rel in by_rel.keys():
        G.add_node(rel)
        degree.setdefault(rel, 0)

    # content link edges (weight=1)
    for rel, src in by_rel.items():
        text = src.read_text(encoding="utf-8", errors="ignore")
        for kind, target in extract_links(text):
            if kind == "wiki":
                resolved = resolve_wikilink(src, target, by_stem)
                if resolved is None:
                    continue
                try:
                    tid = resolved.relative_to(root).as_posix()
                except Exception:
                    continue
                if tid in by_rel and tid != rel:
                    G.add_edge(rel, tid, weight=1.0)
                    bump_degree(rel, tid)
                continue

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
        # skip hub rendering
        if hub_id is not None and node_id == hub_id:
            continue

        # folder nodes: no label, small, dim
        if node_id.startswith("__FOLDER__:"):
            add_node(node_id, "", node_id, "dot", "#334155", size=2.6)
            continue

        # markdown nodes
        if node_id in by_rel:
            p = by_rel[node_id]
            fk = folder_key(node_id, depth=color_depth)
            add_node(node_id, p.stem, node_id, "dot", folder_to_color.get(fk, PALETTE[0]))
        else:
            # non-md nodes
            add_node(node_id, Path(node_id).name, node_id, "box", "#64748b")

    for a, b in G.edges():
        # skip drawing edges to hub (keep it invisible)
        if hub_id is not None and (a == hub_id or b == hub_id):
            continue
        net.add_edge(a, b)

    out_path = Path(args.out).expanduser().resolve()

    html = net.generate_html(notebook=False)
    html = inject_hover_highlight_js(html)
    out_path.write_text(html, encoding="utf-8", errors="strict")

    isolated_md = [nid for nid in by_rel.keys() if degree.get(nid, 0) == 0]

    print(f"OK: wrote {out_path}")
    print(f"Stats: md_nodes={len(by_rel)} total_nodes={G.number_of_nodes()} edges={G.number_of_edges()}")
    print("Layout used: spring_layout (weighted)")
    print(f"Folder backbone: depth={int(args.folder_depth)} weight={float(args.folder_weight)}")
    print(f"Gravity hub: {'OFF' if args.no_hub else 'ON'} (weight={float(args.hub_weight)})")
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