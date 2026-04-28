# React系统性学习

- [1. React 核心认知（总纲）](#1-react-核心认知总纲)
  - [1.1 React 的本质](#11-react-的本质)
  - [1.2 核心运行模型](#12-核心运行模型)
  - [1.3 渲染流程（重点）](#13-渲染流程重点)
  - [1.4 三大驱动更新来源](#14-三大驱动更新来源)
- [2. JSX 与 UI 表达系统](#2-jsx-与-ui-表达系统)
  - [2.1 JSX 本质](#21-jsx-本质)
  - [2.2 JSX 表达能力](#22-jsx-表达能力)
  - [2.3 UI 描述模式](#23-ui-描述模式)
  - [2.4 JSX 限制](#24-jsx-限制)
- [3. 组件系统（结构层）](#3-组件系统结构层)
  - [3.1 组件本质](#31-组件本质)
  - [3.2 组件组织方式](#32-组件组织方式)
  - [3.3 组件组合模式](#33-组件组合模式)
  - [3.4 组件拆分原则](#34-组件拆分原则)
- [4. 数据流系统（通信）](#4-数据流系统通信)
  - [4.1 Props（父 → 子）](#41-props父--子)
  - [4.2 子 → 父通信](#42-子--父通信)
  - [4.3 兄弟通信](#43-兄弟通信)
  - [4.4 跨层通信](#44-跨层通信)
  - [4.5 数据流原则](#45-数据流原则)
- [5. Hooks 系统（核心统一模块）](#5-hooks-系统核心统一模块)
  - [5.1 Hooks 总规则](#51-hooks-总规则)
  - [5.2 状态类 Hooks](#52-状态类-hooks)
    - [useState](#usestate)
    - [useReducer](#usereducer)
  - [5.3 副作用类 Hooks](#53-副作用类-hooks)
    - [useEffect](#useeffect)
  - [5.4 引用类 Hooks](#54-引用类-hooks)
    - [useRef](#useref)
  - [5.5 性能优化 Hooks](#55-性能优化-hooks)
    - [useMemo](#usememo)
    - [useCallback](#usecallback)
    - [memo](#memo)
  - [5.6 上下文 Hooks](#56-上下文-hooks)
    - [useContext](#usecontext)
  - [5.7 自定义 Hooks](#57-自定义-hooks)
- [6. 渲染与副作用机制（重点难点）](#6-渲染与副作用机制重点难点)
  - [6.1 渲染 vs 副作用](#61-渲染-vs-副作用)
  - [6.2 渲染快照机制](#62-渲染快照机制)
  - [6.3 闭包陷阱](#63-闭包陷阱)
  - [6.4 依赖数组本质](#64-依赖数组本质)
  - [6.5 批处理机制](#65-批处理机制)
- [7. 事件系统](#7-事件系统)
  - [7.1 React 事件模型](#71-react-事件模型)
  - [7.2 事件绑定](#72-事件绑定)
  - [7.3 事件传参](#73-事件传参)
  - [7.4 与原生事件区别](#74-与原生事件区别)
- [8. 表单系统](#8-表单系统)
  - [8.1 受控组件](#81-受控组件)
  - [8.2 非受控组件](#82-非受控组件)
  - [8.3 表单状态管理](#83-表单状态管理)
- [9. 样式系统](#9-样式系统)
  - [9.1 className](#91-classname)
  - [9.2 inline style](#92-inline-style)
  - [9.3 CSS Modules](#93-css-modules)
  - [9.4 CSS-in-JS](#94-css-in-js)
  - [9.5 UI 库](#95-ui-库)
- [10. 路由系统](#10-路由系统)
  - [10.1 SPA 概念](#101-spa-概念)
  - [10.2 React Router](#102-react-router)
  - [10.3 路由参数](#103-路由参数)
  - [10.4 嵌套路由](#104-嵌套路由)
- [11. 状态管理体系（全局）](#11-状态管理体系全局)
  - [11.1 为什么需要](#111-为什么需要)
  - [11.2 方案对比](#112-方案对比)
  - [11.3 Redux 核心](#113-redux-核心)
- [12. 性能优化体系](#12-性能优化体系)
  - [12.1 渲染优化](#121-渲染优化)
  - [12.2 结构优化](#122-结构优化)
  - [12.3 列表优化](#123-列表优化)
- [13. 工程化体系](#13-工程化体系)
  - [13.1 项目结构设计](#131-项目结构设计)
  - [13.2 代码规范（ESLint / Prettier）](#132-代码规范eslint--prettier)
  - [13.3 API 管理](#133-api-管理)
  - [13.4 环境变量](#134-环境变量)
  - [13.5 组件设计模式](#135-组件设计模式)
- [14. TypeScript + React](#14-typescript--react)
  - [14.1 Props 类型](#141-props-类型)
  - [14.2 Hooks 类型](#142-hooks-类型)
  - [14.3 事件类型](#143-事件类型)
  - [14.4 泛型组件](#144-泛型组件)
- [15. React 原理体系](#15-react-原理体系)
  - [15.1 虚拟 DOM](#151-虚拟-dom)
  - [15.2 Diff 算法](#152-diff-算法)
  - [15.3 Fiber](#153-fiber)
  - [15.4 调度机制（概念级）](#154-调度机制概念级)
- [16. 进阶模式](#16-进阶模式)
  - [16.1 高阶组件（HOC）](#161-高阶组件hoc)
  - [16.2 Render Props](#162-render-props)
  - [16.3 Compound Components](#163-compound-components)
  - [16.4 Portals](#164-portals)
  - [16.5 Suspense / lazy](#165-suspense--lazy)
- [17. 数据请求体系](#17-数据请求体系)
  - [17.1 fetch / axios](#171-fetch--axios)
  - [17.2 请求状态管理](#172-请求状态管理)
  - [17.3 竞态问题](#173-竞态问题)
  - [17.4 副作用管理](#174-副作用管理)
- [18. 实战能力（最关键）](#18-实战能力最关键)
  - [18.1 状态设计能力](#181-状态设计能力)
  - [18.2 组件拆分能力](#182-组件拆分能力)
  - [18.3 数据流设计](#183-数据流设计)
  - [18.4 异步处理](#184-异步处理)
  - [18.5 错误处理](#185-错误处理)
- [19. 调试与排错](#19-调试与排错)
  - [19.1 常见错误类型](#191-常见错误类型)
  - [19.2 React DevTools](#192-react-devtools)
  - [19.3 调试思路](#193-调试思路)


## 1. React 核心认知（总纲）

### 1.1 React 的本质

**React 是一个 UI 函数**：给定相同的输入（state + props），永远产出相同的 UI 输出。

```
UI = f(state)
```

**声明式 vs 命令式**：

|      | 命令式（jQuery）               | 声明式（React）                |
| ---- | ------------------------------ | ------------------------------ |
| 思维 | 描述"怎么做"                   | 描述"是什么"                   |
| 代码 | `$('#btn').addClass('active')` | `<Button active={isActive} />` |
| 维护 | 状态分散，难追踪               | 状态集中，UI 可预测            |

```js
// 命令式：手动操作 DOM
function toggleMenu() {
  const menu = document.querySelector('.menu')
  if (menu.classList.contains('open')) {
    menu.classList.remove('open')
    menu.style.height = '0'
  } else {
    menu.classList.add('open')
    menu.style.height = menu.scrollHeight + 'px'
  }
}

// 声明式：描述 UI 应该长什么样
function Menu({ items }) {
  const [isOpen, setIsOpen] = useState(false)
  return (
    <div className={`menu ${isOpen ? 'open' : ''}`} style={{ height: isOpen ? 'auto' : 0 }}>
      {items.map(item => <MenuItem key={item.id} {...item} />)}
    </div>
  )
}
```

### 1.2 核心运行模型

- **组件 = 函数**：每个组件就是一个普通 JS 函数，接受 props，返回 JSX
- **渲染 = 执行函数**：React 调用你的组件函数，获得 UI 描述
- **更新 = 重新执行函数**：state 变化时，React 重新执行组件函数

```js
// React 内部逻辑（简化）
function render(Component, props) {
  const ui = Component(props) // 执行组件函数
  commitToDOM(ui)             // 提交到 DOM
}
```

### 1.3 渲染流程（重点）

```
state/props 变化
  → Render 阶段（执行组件函数，生成新 Fiber 树）
  → Diff 阶段（新旧 Fiber 树对比，计算最小变更）
  → Commit 阶段（将变更应用到真实 DOM）
  → 执行 useLayoutEffect
  → 浏览器绘制
  → 执行 useEffect
```

### 1.4 三大驱动更新来源

```js
function Parent() {
  const [count, setCount] = useState(0)  // ① state 变化
  return <Child count={count} />          // ② 父组件渲染导致子组件渲染
}

function Child({ count }) {               // ③ props 变化
  return <div>{count}</div>
}
```

---

## 2. JSX 与 UI 表达系统

### 2.1 JSX 本质

JSX 是 `React.createElement` 的语法糖，编译后变成普通 JS 对象（虚拟 DOM 节点）：

```jsx
// 你写的 JSX
const element = (
  <div className="container" onClick={handleClick}>
    <h1>Hello {name}</h1>
    <p>Count: {count}</p>
  </div>
)

// Babel 编译后
const element = React.createElement(
  'div',
  { className: 'container', onClick: handleClick },
  React.createElement('h1', null, 'Hello ', name),
  React.createElement('p', null, 'Count: ', count)
)

// 实际产出的 JS 对象（虚拟 DOM）
{
  type: 'div',
  props: {
    className: 'container',
    onClick: handleClick,
    children: [
      { type: 'h1', props: { children: ['Hello ', name] } },
      { type: 'p',  props: { children: ['Count: ', count] } }
    ]
  }
}
```

**JSX ≠ HTML**：JSX 里用 `className` 而不是 `class`，用 `htmlFor` 而不是 `for`，事件用驼峰命名。

### 2.2 JSX 表达能力

**插值 `{}`**：大括号内可以放任意 JS 表达式（不能是语句）：

```jsx
function UserCard({ user, score }) {
  const level = score > 1000 ? 'Gold' : score > 500 ? 'Silver' : 'Bronze'
  const avatar = user.avatar || `https://ui-avatars.com/api/?name=${user.name}`

  return (
    <div className="card">
      <img src={avatar} alt={user.name} />
      <h2>{user.name.toUpperCase()}</h2>
      <span className={`badge badge-${level.toLowerCase()}`}>
        {level} · {score.toLocaleString()} pts
      </span>
      <time dateTime={user.joinedAt}>
        Joined {new Date(user.joinedAt).toLocaleDateString('zh-CN')}
      </time>
    </div>
  )
}
```

**条件渲染**：

```jsx
function Dashboard({ user, isLoading, error, data }) {
  // 早返回（guard clause）
  if (isLoading) return <Spinner size="large" />
  if (error) return <ErrorBoundary message={error.message} onRetry={fetchData} />
  if (!user) return <Navigate to="/login" />

  return (
    <div>
      {/* 短路求值：只在 user.isAdmin 为真时渲染 */}
      {user.isAdmin && <AdminPanel userId={user.id} />}

      {/* 三元：二选一 */}
      {data.items.length > 0
        ? <DataTable items={data.items} columns={columns} />
        : <EmptyState message="暂无数据" action={<Button onClick={fetchData}>刷新</Button>} />
      }

      {/* 复杂条件抽成变量 */}
      {(() => {
        switch (user.role) {
          case 'admin': return <AdminView />
          case 'editor': return <EditorView />
          default: return <ReadonlyView />
        }
      })()}
    </div>
  )
}
```

**列表渲染**：

```jsx
function OrderList({ orders }) {
  return (
    <ul>
      {orders
        .filter(o => o.status !== 'cancelled')
        .sort((a, b) => new Date(b.createdAt) - new Date(a.createdAt))
        .map(order => (
          <li key={order.id}>
            <OrderItem
              order={order}
              onCancel={() => cancelOrder(order.id)}
            />
          </li>
        ))
      }
    </ul>
  )
}
```

### 2.3 UI 描述模式

**分支 UI**、**列表 UI**、**组合 UI** 经常组合使用：

```jsx
function ProductGrid({ category, filters, sortBy }) {
  const products = useProducts({ category, filters, sortBy })

  return (
    <section>
      <header>
        <h2>{category.name}</h2>
        <SortSelector value={sortBy} onChange={setSortBy} />
        <FilterPanel filters={filters} onChange={setFilters} />
      </header>

      {products.isLoading ? (
        <SkeletonGrid count={12} />
      ) : (
        <div className="grid">
          {products.data.map(p => (
            <ProductCard
              key={p.id}
              product={p}
              badge={p.stock < 5 ? `仅剩${p.stock}件` : null}
              ribbon={p.isNew ? 'NEW' : p.discount > 0.3 ? 'HOT' : null}
            />
          ))}
        </div>
      )}

      <Pagination
        total={products.total}
        page={products.page}
        onChange={products.setPage}
      />
    </section>
  )
}
```

### 2.4 JSX 限制

**不能写语句（if / for）**：只能写表达式。

```jsx
// ❌ 错误：if 是语句
const el = <div>{if (show) <span>hi</span>}</div>

// ✅ 正确：三元表达式
const el = <div>{show ? <span>hi</span> : null}</div>
```

**不能渲染对象**：

```jsx
const obj = { name: 'Alice' }
// ❌ 报错：Objects are not valid as a React child
return <div>{obj}</div>

// ✅ 访问具体属性
return <div>{obj.name}</div>

// ✅ 数组可以渲染（每项是字符串/数字/元素）
return <div>{['Alice', 'Bob', 'Charlie'].map(name => <span key={name}>{name}</span>)}</div>
```

**key 机制**：key 帮助 React 识别哪些列表项发生了变化，必须是同层唯一且稳定的值：

```jsx
// ❌ 用 index 作为 key：排序/删除时会导致状态错乱
{items.map((item, index) => <Input key={index} defaultValue={item.text} />)}

// ✅ 用稳定唯一 ID
{items.map(item => <Input key={item.id} defaultValue={item.text} />)}
```

---

## 3. 组件系统（结构层）

### 3.1 组件本质

组件是一个**纯函数**：相同 props → 相同 UI，没有副作用（副作用放 useEffect）。

```jsx
// 纯函数组件：可预测、可测试
function PriceTag({ price, currency = 'CNY', discount = 0 }) {
  const finalPrice = price * (1 - discount)
  const formatter = new Intl.NumberFormat('zh-CN', {
    style: 'currency',
    currency,
  })

  return (
    <span className="price-tag">
      {discount > 0 && (
        <del className="original">{formatter.format(price)}</del>
      )}
      <strong className="final">{formatter.format(finalPrice)}</strong>
      {discount > 0 && (
        <em className="discount">-{(discount * 100).toFixed(0)}%</em>
      )}
    </span>
  )
}
```

**单向数据流**：数据从父 → 子，子不能直接修改父的 state。

### 3.2 组件组织方式

```
src/
├── pages/          # 页面组件（对应路由，负责数据获取和布局）
│   ├── HomePage/
│   └── ProductDetailPage/
├── features/       # 业务组件（特定业务逻辑，不可复用）
│   ├── cart/
│   └── checkout/
└── components/     # 基础组件（通用 UI，无业务逻辑）
    ├── Button/
    ├── Modal/
    └── DataTable/
```

### 3.3 组件组合模式

**children**：

```jsx
// 通用容器组件
function Card({ title, footer, children, className = '' }) {
  return (
    <div className={`card ${className}`}>
      {title && <div className="card-header">{title}</div>}
      <div className="card-body">{children}</div>
      {footer && <div className="card-footer">{footer}</div>}
    </div>
  )
}

// 使用
<Card
  title={<h2>订单详情 <Badge>待付款</Badge></h2>}
  footer={<><Button variant="primary">立即付款</Button><Button>取消订单</Button></>}
>
  <OrderInfo order={order} />
  <ItemList items={order.items} />
</Card>
```

**插槽模式（named slots via props）**：

```jsx
function PageLayout({ sidebar, toolbar, main, footer }) {
  return (
    <div className="layout">
      <aside className="layout-sidebar">{sidebar}</aside>
      <div className="layout-content">
        <div className="layout-toolbar">{toolbar}</div>
        <main className="layout-main">{main}</main>
        <footer className="layout-footer">{footer}</footer>
      </div>
    </div>
  )
}

// 使用：像插槽一样传入各区域内容
<PageLayout
  sidebar={<NavMenu items={menuItems} />}
  toolbar={<SearchBar onSearch={handleSearch} />}
  main={<ProductList products={products} />}
  footer={<Pagination {...paginationProps} />}
/>
```

**组合优于继承**：React 中几乎不需要继承，用组合解决所有复用问题。

### 3.4 组件拆分原则

```jsx
// ❌ 拆分过度：每个 <p> 都是组件
// ❌ 不拆分：一个组件 500 行

// ✅ 合理拆分依据：
// 1. 单一职责：一个组件只做一件事
// 2. 可复用：多处使用时抽取
// 3. 可测试：逻辑复杂时抽取
// 4. 性能：频繁更新的部分隔离

// 拆分前（300 行的大组件）
function ProductPage() {
  // 图片轮播逻辑
  // 规格选择逻辑
  // 价格计算逻辑
  // 购物车逻辑
  // 评论列表逻辑
  // ...巨量 JSX...
}

// 拆分后
function ProductPage() {
  const product = useProduct(id)
  const [selectedSku, setSelectedSku] = useState(null)

  return (
    <div>
      <ProductGallery images={product.images} />
      <ProductInfo product={product} />
      <SkuSelector skus={product.skus} value={selectedSku} onChange={setSelectedSku} />
      <PriceSummary sku={selectedSku} promotions={product.promotions} />
      <AddToCartButton productId={product.id} skuId={selectedSku?.id} />
      <ReviewSection productId={product.id} />
    </div>
  )
}
```

---

## 4. 数据流系统（通信）

### 4.1 Props（父 → 子）

Props 是**只读**的，子组件不能修改它。

**简单案例**：

```jsx
// 父组件持有数据，通过 props 传给子组件
function Parent() {
  const user = { name: '张三', age: 28 }
  return <Child user={user} greeting="你好" />
}

function Child({ user, greeting }) {
  // ❌ 不能修改 props
  // user.name = '李四'

  return <p>{greeting}，{user.name}！你今年 {user.age} 岁。</p>
}
```

```jsx
// 复杂 props 示例
function DataTable({ columns, data, loading, pagination, onSort, onRowClick, renderActions }) {
  return (
    <div className="table-wrapper">
      {loading && <LoadingOverlay />}
      <table>
        <thead>
          <tr>
            {columns.map(col => (
              <th
                key={col.key}
                style={{ width: col.width }}
                onClick={() => col.sortable && onSort(col.key)}
              >
                {col.title}
                {col.sortable && <SortIcon />}
              </th>
            ))}
            {renderActions && <th>操作</th>}
          </tr>
        </thead>
        <tbody>
          {data.map(row => (
            <tr key={row.id} onClick={() => onRowClick?.(row)}>
              {columns.map(col => (
                <td key={col.key}>
                  {col.render ? col.render(row[col.key], row) : row[col.key]}
                </td>
              ))}
              {renderActions && <td>{renderActions(row)}</td>}
            </tr>
          ))}
        </tbody>
      </table>
      {pagination && <Pagination {...pagination} />}
    </div>
  )
}

// 调用
<DataTable
  columns={[
    { key: 'name', title: '姓名', sortable: true },
    { key: 'status', title: '状态', render: (val) => <StatusBadge status={val} /> },
    { key: 'amount', title: '金额', render: (val) => `¥${val.toFixed(2)}`, sortable: true },
  ]}
  data={users}
  loading={isLoading}
  pagination={{ total: 100, page: 1, pageSize: 10, onChange: setPage }}
  onSort={handleSort}
  onRowClick={handleRowClick}
  renderActions={(row) => (
    <>
      <Button size="sm" onClick={() => handleEdit(row)}>编辑</Button>
      <Button size="sm" variant="danger" onClick={() => handleDelete(row.id)}>删除</Button>
    </>
  )}
/>
```

### 4.2 子 → 父通信

通过**回调函数** props 实现：

**简单案例**：

```jsx
// 父组件传入回调，子组件调用时把数据"还给"父组件
function Parent() {
  const [msg, setMsg] = useState('（等待子组件输入）')
  return (
    <div>
      <p>父组件收到：{msg}</p>
      <Child onSend={setMsg} />
    </div>
  )
}

function Child({ onSend }) {
  const [input, setInput] = useState('')
  return (
    <>
      <input value={input} onChange={e => setInput(e.target.value)} />
      <button onClick={() => onSend(input)}>发送给父组件</button>
    </>
  )
}
```

```jsx
// 父组件持有状态，子组件通过回调修改
function FilterableList() {
  const [filters, setFilters] = useState({ keyword: '', status: 'all', dateRange: null })
  const [selectedIds, setSelectedIds] = useState(new Set())

  function handleFilterChange(key, value) {
    setFilters(prev => ({ ...prev, [key]: value }))
  }

  function handleSelectAll(checked) {
    setSelectedIds(checked ? new Set(data.map(d => d.id)) : new Set())
  }

  function handleSelectOne(id, checked) {
    setSelectedIds(prev => {
      const next = new Set(prev)
      checked ? next.add(id) : next.delete(id)
      return next
    })
  }

  return (
    <div>
      <FilterBar
        filters={filters}
        onChange={handleFilterChange}   // 子 → 父：更新 filters
      />
      <BatchActions
        selectedIds={selectedIds}
        onDelete={handleBatchDelete}    // 子 → 父：触发删除
      />
      <List
        data={filteredData}
        selectedIds={selectedIds}
        onSelectAll={handleSelectAll}
        onSelectOne={handleSelectOne}
      />
    </div>
  )
}
```

### 4.3 兄弟通信

**状态提升（Lifting State Up）**：将共享状态提升到最近公共祖先：

**简单案例**：

```jsx
// 兄弟组件 A 和 B 无法直接通信，把共享状态提到父组件
function Parent() {
  const [count, setCount] = useState(0)
  return (
    <>
      <ButtonA onIncrement={() => setCount(c => c + 1)} />
      <DisplayB count={count} />
    </>
  )
}

function ButtonA({ onIncrement }) {
  return <button onClick={onIncrement}>+1</button>
}

function DisplayB({ count }) {
  return <p>当前计数：{count}</p>
}
```

```jsx
// ❌ 兄弟组件无法直接通信
function SearchBox() { /* 不知道 ResultList 的存在 */ }
function ResultList() { /* 不知道 SearchBox 的存在 */ }

// ✅ 状态提升到父组件
function SearchPage() {
  const [query, setQuery] = useState('')
  const [filters, setFilters] = useState({ category: 'all', priceRange: [0, 10000] })
  const results = useSearch(query, filters)

  return (
    <div>
      <SearchBox
        value={query}
        onChange={setQuery}
        onClear={() => { setQuery(''); setFilters({ category: 'all', priceRange: [0, 10000] }) }}
      />
      <FilterSidebar
        filters={filters}
        onChange={setFilters}
        resultCount={results.total}
      />
      <ResultList
        items={results.data}
        loading={results.isLoading}
        query={query}
      />
    </div>
  )
}
```

### 4.4 跨层通信

**Context**：避免 props drilling（多层透传）：

**简单案例**：

```jsx
// 不用 Context：每层都要手动传 theme（props drilling）
// <App theme="dark">
//   <Layout theme="dark">
//     <Sidebar theme="dark">
//       <Button theme="dark" />   ← 只有这里需要，却穿透了3层

// 用 Context：直接跨层获取
const ThemeContext = createContext('light')

function App() {
  return (
    <ThemeContext.Provider value="dark">
      <Layout />   {/* 中间层不需要感知 theme */}
    </ThemeContext.Provider>
  )
}

function Layout() {
  return <Sidebar />   // 不需要传 theme
}

function Sidebar() {
  return <Button />    // 不需要传 theme
}

function Button() {
  const theme = useContext(ThemeContext)  // 直接取到 "dark"
  return <button className={`btn--${theme}`}>点我</button>
}
```

```jsx
// 创建 Context
const ThemeContext = createContext('light')
const UserContext = createContext(null)

// Provider 提供数据
function App() {
  const [theme, setTheme] = useState('light')
  const [user, setUser] = useState(null)

  return (
    <ThemeContext.Provider value={{ theme, setTheme }}>
      <UserContext.Provider value={{ user, setUser }}>
        <Router>
          <Layout />
        </Router>
      </UserContext.Provider>
    </ThemeContext.Provider>
  )
}

// 任意深度子组件消费
function UserAvatar() {
  const { user } = useContext(UserContext)
  const { theme } = useContext(ThemeContext)

  if (!user) return null
  return (
    <img
      src={user.avatar}
      className={`avatar avatar--${theme}`}
      alt={user.name}
    />
  )
}
```

### 4.5 数据流原则

- **单向数据流**：数据只从上往下流，不能反向
- **单一数据源（Single Source of Truth）**：同一份数据只存一处，其他地方派生

```jsx
// ❌ 双重 state：两份数据容易不同步
function Cart() {
  const [items, setItems] = useState([])
  const [total, setTotal] = useState(0) // 冗余！可派生

  function addItem(item) {
    setItems(prev => [...prev, item])
    setTotal(prev => prev + item.price) // 容易遗漏/错误
  }
}

// ✅ 派生数据
function Cart() {
  const [items, setItems] = useState([])
  const total = items.reduce((sum, item) => sum + item.price * item.qty, 0) // 自动同步

  function addItem(item) {
    setItems(prev => [...prev, item]) // 只维护一份数据
  }
}
```

---

## 5. Hooks 系统（核心统一模块）

### 5.1 Hooks 总规则

- **只能在顶层调用**：不能在条件、循环、嵌套函数中调用
- **只能在函数组件或自定义 Hook 中调用**
- **本质**：React 用**调用顺序**（索引）来记录每个 Hook 的状态

```jsx
// ❌ 条件中调用：调用顺序不稳定，会导致状态错乱
function Component({ isLoggedIn }) {
  if (isLoggedIn) {
    const [user, setUser] = useState(null) // 有时第1个，有时没有
  }
  const [count, setCount] = useState(0)   // 有时第1个，有时第2个
}

// ✅ 条件放在 Hook 内部
function Component({ isLoggedIn }) {
  const [user, setUser] = useState(null)  // 始终是第1个 Hook
  const [count, setCount] = useState(0)  // 始终是第2个 Hook

  useEffect(() => {
    if (!isLoggedIn) return // 条件放里面
    fetchUser().then(setUser)
  }, [isLoggedIn])
}
```

### 5.2 状态类 Hooks

#### useState

```jsx
// 基础用法
const [state, setState] = useState(initialValue)

// 函数式更新：当新 state 依赖旧 state 时，必须用函数式
function Counter() {
  const [count, setCount] = useState(0)

  // ❌ 批处理时可能出问题
  function handleTripleClick() {
    setCount(count + 1)
    setCount(count + 1) // 还是基于旧的 count，结果只 +1
    setCount(count + 1)
  }

  // ✅ 函数式更新：每次基于最新 state
  function handleTripleClickFixed() {
    setCount(c => c + 1)
    setCount(c => c + 1) // 基于上一次更新后的值
    setCount(c => c + 1) // 结果 +3
  }

  return <button onClick={handleTripleClickFixed}>{count}</button>
}

// 惰性初始化：initialValue 是复杂计算时，传函数避免每次渲染都执行
function ExpensiveComponent() {
  // ❌ 每次渲染都执行 parseFromLocalStorage（即使只用第一次）
  const [data, setData] = useState(parseFromLocalStorage('key'))

  // ✅ 只在挂载时执行一次
  const [data, setData] = useState(() => parseFromLocalStorage('key'))
}

// 复杂 state 示例：电商购物车
function useCartState() {
  const [cart, setCart] = useState({
    items: [],
    couponCode: '',
    shippingAddress: null,
  })

  const addItem = useCallback((product, qty = 1) => {
    setCart(prev => {
      const existing = prev.items.find(i => i.productId === product.id)
      if (existing) {
        return {
          ...prev,
          items: prev.items.map(i =>
            i.productId === product.id
              ? { ...i, qty: i.qty + qty }
              : i
          )
        }
      }
      return {
        ...prev,
        items: [...prev.items, { productId: product.id, product, qty, price: product.price }]
      }
    })
  }, [])

  const removeItem = useCallback((productId) => {
    setCart(prev => ({ ...prev, items: prev.items.filter(i => i.productId !== productId) }))
  }, [])

  const total = cart.items.reduce((sum, i) => sum + i.price * i.qty, 0)

  return { cart, addItem, removeItem, total }
}
```

**state 快照机制**：每次渲染，state 的值是固定的（见第6节详细讲解）。

#### useReducer

适合**复杂状态逻辑**、多个子值相互关联、或下一个 state 依赖于前一个 state 的场景：

```jsx
// 复杂表单的 useReducer
const initialState = {
  step: 1,
  personalInfo: { name: '', email: '', phone: '' },
  addressInfo: { province: '', city: '', detail: '' },
  paymentInfo: { method: 'alipay', cardNumber: '' },
  errors: {},
  isSubmitting: false,
}

function checkoutReducer(state, action) {
  switch (action.type) {
    case 'SET_FIELD':
      return {
        ...state,
        [action.section]: {
          ...state[action.section],
          [action.field]: action.value,
        },
        errors: { ...state.errors, [`${action.section}.${action.field}`]: '' },
      }

    case 'NEXT_STEP':
      const errors = validateStep(state, state.step)
      if (Object.keys(errors).length > 0) {
        return { ...state, errors }
      }
      return { ...state, step: state.step + 1, errors: {} }

    case 'PREV_STEP':
      return { ...state, step: state.step - 1 }

    case 'SUBMIT_START':
      return { ...state, isSubmitting: true }

    case 'SUBMIT_SUCCESS':
      return { ...initialState }

    case 'SUBMIT_FAILURE':
      return { ...state, isSubmitting: false, errors: { submit: action.error } }

    default:
      throw new Error(`Unknown action: ${action.type}`)
  }
}

function CheckoutForm() {
  const [state, dispatch] = useReducer(checkoutReducer, initialState)

  function handleFieldChange(section, field, value) {
    dispatch({ type: 'SET_FIELD', section, field, value })
  }

  async function handleSubmit() {
    dispatch({ type: 'SUBMIT_START' })
    try {
      await submitOrder(state)
      dispatch({ type: 'SUBMIT_SUCCESS' })
    } catch (err) {
      dispatch({ type: 'SUBMIT_FAILURE', error: err.message })
    }
  }

  return (
    <div>
      <StepIndicator current={state.step} total={3} />
      {state.step === 1 && (
        <PersonalInfoStep
          data={state.personalInfo}
          errors={state.errors}
          onChange={(field, value) => handleFieldChange('personalInfo', field, value)}
        />
      )}
      {state.step === 2 && (
        <AddressStep
          data={state.addressInfo}
          errors={state.errors}
          onChange={(field, value) => handleFieldChange('addressInfo', field, value)}
        />
      )}
      {state.step === 3 && (
        <PaymentStep
          data={state.paymentInfo}
          errors={state.errors}
          onChange={(field, value) => handleFieldChange('paymentInfo', field, value)}
        />
      )}
      <div className="step-actions">
        {state.step > 1 && <Button onClick={() => dispatch({ type: 'PREV_STEP' })}>上一步</Button>}
        {state.step < 3
          ? <Button onClick={() => dispatch({ type: 'NEXT_STEP' })}>下一步</Button>
          : <Button loading={state.isSubmitting} onClick={handleSubmit}>提交订单</Button>
        }
      </div>
    </div>
  )
}
```

### 5.3 副作用类 Hooks

#### useEffect

**副作用**：与渲染无关的操作——数据请求、订阅、手动 DOM 操作、定时器等。

**执行时机**：

```
render → commit（更新 DOM）→ 浏览器绘制 → useEffect 执行
```

```jsx
// 依赖数组的三种形式
useEffect(() => { /* 每次渲染后都执行 */ })
useEffect(() => { /* 只在挂载时执行一次 */ }, [])
useEffect(() => { /* dep1 或 dep2 变化时执行 */ }, [dep1, dep2])

// 清理函数：组件卸载或下次 effect 执行前调用
useEffect(() => {
  const subscription = eventBus.subscribe('update', handleUpdate)
  return () => subscription.unsubscribe() // 清理
}, [])

// 复杂示例：实时搜索（防抖 + 竞态处理）
function SearchResults({ query }) {
  const [results, setResults] = useState([])
  const [loading, setLoading] = useState(false)
  const [error, setError] = useState(null)

  useEffect(() => {
    if (!query.trim()) {
      setResults([])
      return
    }

    let cancelled = false // 处理竞态：旧请求的结果不覆盖新请求
    setLoading(true)
    setError(null)

    const timer = setTimeout(async () => {
      try {
        const data = await searchAPI(query)
        if (!cancelled) {
          setResults(data)
          setLoading(false)
        }
      } catch (err) {
        if (!cancelled) {
          setError(err.message)
          setLoading(false)
        }
      }
    }, 300) // 防抖 300ms

    return () => {
      cancelled = true
      clearTimeout(timer)
    }
  }, [query])

  if (loading) return <Spinner />
  if (error) return <ErrorMessage message={error} />
  return <ResultList items={results} />
}
```

**useLayoutEffect**：在 DOM 更新后、浏览器绘制前同步执行。用于需要在用户看到前测量/修改 DOM 的场景（如 Tooltip 定位）：

```jsx
function Tooltip({ targetRef, children }) {
  const tooltipRef = useRef()
  const [position, setPosition] = useState({ top: 0, left: 0 })

  useLayoutEffect(() => {
    const target = targetRef.current
    const tooltip = tooltipRef.current
    if (!target || !tooltip) return

    const targetRect = target.getBoundingClientRect()
    const tooltipRect = tooltip.getBoundingClientRect()

    setPosition({
      top: targetRect.bottom + 8,
      left: targetRect.left + (targetRect.width - tooltipRect.width) / 2,
    })
  }) // 每次渲染都重新计算位置

  return (
    <div ref={tooltipRef} className="tooltip" style={position}>
      {children}
    </div>
  )
}
```

### 5.4 引用类 Hooks

#### useRef

有两个完全不同的用途：

**① DOM 引用**：

```jsx
function VideoPlayer({ src, autoPlay }) {
  const videoRef = useRef(null)
  const [isPlaying, setIsPlaying] = useState(autoPlay)

  useEffect(() => {
    const video = videoRef.current
    if (!video) return
    isPlaying ? video.play() : video.pause()
  }, [isPlaying])

  // 暴露给父组件
  useImperativeHandle(forwardedRef, () => ({
    play: () => setIsPlaying(true),
    pause: () => setIsPlaying(false),
    seek: (time) => { videoRef.current.currentTime = time },
  }))

  return (
    <div>
      <video ref={videoRef} src={src} />
      <button onClick={() => setIsPlaying(p => !p)}>
        {isPlaying ? '暂停' : '播放'}
      </button>
    </div>
  )
}
```

**② 可变容器（不触发渲染）**：用于存储不需要触发渲染的值（定时器 ID、上一次的值、是否首次渲染等）：

```jsx
function useInterval(callback, delay) {
  const savedCallback = useRef(callback)

  // 保持 callback 引用最新，避免闭包陷阱
  useEffect(() => {
    savedCallback.current = callback
  }, [callback])

  useEffect(() => {
    if (delay === null) return
    const id = setInterval(() => savedCallback.current(), delay)
    return () => clearInterval(id)
  }, [delay])
}

// 获取上一次的值
function usePrevious(value) {
  const prevRef = useRef()
  useEffect(() => {
    prevRef.current = value
  })
  return prevRef.current
}

function PriceDisplay({ price }) {
  const prevPrice = usePrevious(price)
  const trend = prevPrice !== undefined
    ? price > prevPrice ? 'up' : price < prevPrice ? 'down' : 'flat'
    : 'flat'

  return (
    <span className={`price price--${trend}`}>
      ¥{price.toFixed(2)}
      {trend !== 'flat' && <Arrow direction={trend} />}
    </span>
  )
}
```

### 5.5 性能优化 Hooks

#### useMemo

缓存**计算结果**，避免每次渲染都重新计算：

```jsx
function DataAnalytics({ rawData, filters, groupBy }) {
  // ❌ 每次父组件渲染都重新计算，即使 rawData/filters/groupBy 没变
  const processedData = expensiveProcess(rawData, filters, groupBy)

  // ✅ 只在依赖变化时重新计算
  const processedData = useMemo(() => {
    return rawData
      .filter(row => matchesFilters(row, filters))
      .reduce((groups, row) => {
        const key = row[groupBy]
        if (!groups[key]) groups[key] = { key, items: [], total: 0 }
        groups[key].items.push(row)
        groups[key].total += row.amount
        return groups
      }, {})
  }, [rawData, filters, groupBy])

  // 引用稳定：传给子组件不会导致不必要的重渲染
  return <Chart data={processedData} />
}
```

#### useCallback

缓存**函数引用**，避免每次渲染生成新函数导致子组件不必要的重渲染：

```jsx
// ❌ 每次渲染 handleDelete 是新函数引用 → Row 每次都重渲染
function TodoList() {
  const [todos, setTodos] = useState([])

  const handleDelete = (id) => { // 每次新函数
    setTodos(prev => prev.filter(t => t.id !== id))
  }

  return todos.map(todo => (
    <Row key={todo.id} todo={todo} onDelete={handleDelete} />
  ))
}

// ✅ 函数引用稳定，配合 memo 避免不必要渲染
function TodoList() {
  const [todos, setTodos] = useState([])

  const handleDelete = useCallback((id) => {
    setTodos(prev => prev.filter(t => t.id !== id))
  }, []) // 依赖空数组：函数永远不变

  const handleToggle = useCallback((id) => {
    setTodos(prev => prev.map(t => t.id === id ? { ...t, done: !t.done } : t))
  }, [])

  return todos.map(todo => (
    <Row key={todo.id} todo={todo} onDelete={handleDelete} onToggle={handleToggle} />
  ))
}

const Row = memo(function Row({ todo, onDelete, onToggle }) {
  return (
    <li>
      <input type="checkbox" checked={todo.done} onChange={() => onToggle(todo.id)} />
      <span>{todo.text}</span>
      <button onClick={() => onDelete(todo.id)}>删除</button>
    </li>
  )
})
```

#### memo

对**组件**进行优化：props 未变化时跳过渲染：

```jsx
// 默认：浅比较 props
const ExpensiveChart = memo(function Chart({ data, config }) {
  // 只在 data 或 config 引用变化时重渲染
  return <canvas ref={canvasRef} />
})

// 自定义比较函数
const DataRow = memo(
  function DataRow({ row, columns, isSelected, onSelect }) {
    return (
      <tr className={isSelected ? 'selected' : ''} onClick={() => onSelect(row.id)}>
        {columns.map(col => <td key={col.key}>{col.render(row)}</td>)}
      </tr>
    )
  },
  (prevProps, nextProps) => {
    // 返回 true = props 相同 = 跳过渲染
    return (
      prevProps.row === nextProps.row &&
      prevProps.isSelected === nextProps.isSelected &&
      prevProps.columns === nextProps.columns
      // onSelect 刻意不比较，假设父组件已用 useCallback 保证稳定
    )
  }
)
```

### 5.6 上下文 Hooks

#### useContext

```jsx
// 1. 创建 Context（带默认值）
const AuthContext = createContext({
  user: null,
  token: null,
  login: async () => {},
  logout: () => {},
})

// 2. 自定义 Hook 封装（方便使用 + 类型安全）
function useAuth() {
  const ctx = useContext(AuthContext)
  if (!ctx) throw new Error('useAuth must be used within AuthProvider')
  return ctx
}

// 3. Provider 实现
function AuthProvider({ children }) {
  const [user, setUser] = useState(null)
  const [token, setToken] = useState(() => localStorage.getItem('token'))

  useEffect(() => {
    if (token) fetchUserByToken(token).then(setUser).catch(() => setToken(null))
  }, [token])

  const login = useCallback(async (email, password) => {
    const { user, token } = await loginAPI(email, password)
    localStorage.setItem('token', token)
    setToken(token)
    setUser(user)
  }, [])

  const logout = useCallback(() => {
    localStorage.removeItem('token')
    setToken(null)
    setUser(null)
  }, [])

  return (
    <AuthContext.Provider value={{ user, token, login, logout }}>
      {children}
    </AuthContext.Provider>
  )
}

// 4. 任意深度使用
function UserMenu() {
  const { user, logout } = useAuth()
  return (
    <div>
      <img src={user.avatar} alt={user.name} />
      <button onClick={logout}>退出登录</button>
    </div>
  )
}
```

**Context 性能注意**：Context value 变化会导致所有消费者重渲染，需要合理拆分：

```jsx
// ❌ 高频更新（鼠标位置）与低频数据（用户信息）放一个 Context
const AppContext = createContext({ user, mousePosition })

// ✅ 拆分 Context，减少不必要的重渲染
const UserContext = createContext(null)       // 低频
const MouseContext = createContext({ x: 0, y: 0 }) // 高频，只有需要的组件消费
```

### 5.7 自定义 Hooks

将**状态逻辑**抽离为可复用的 Hook：

```jsx
// 复杂自定义 Hook：带缓存、重试、轮询的数据请求
function useFetch(url, options = {}) {
  const {
    immediate = true,
    pollingInterval = null,
    retryCount = 0,
    retryDelay = 1000,
    transform = data => data,
  } = options

  const [state, dispatch] = useReducer(
    (s, a) => ({ ...s, ...a }),
    { data: null, loading: false, error: null }
  )

  const retriesLeft = useRef(retryCount)
  const abortController = useRef(null)

  const execute = useCallback(async () => {
    abortController.current?.abort()
    abortController.current = new AbortController()
    retriesLeft.current = retryCount

    dispatch({ loading: true, error: null })

    const attempt = async () => {
      try {
        const res = await fetch(url, {
          signal: abortController.current.signal,
          ...options.fetchOptions,
        })
        if (!res.ok) throw new Error(`HTTP ${res.status}: ${res.statusText}`)
        const raw = await res.json()
        dispatch({ data: transform(raw), loading: false })
      } catch (err) {
        if (err.name === 'AbortError') return
        if (retriesLeft.current > 0) {
          retriesLeft.current--
          setTimeout(attempt, retryDelay)
        } else {
          dispatch({ error: err.message, loading: false })
        }
      }
    }

    await attempt()
  }, [url, retryCount, retryDelay])

  useEffect(() => {
    if (immediate) execute()
    return () => abortController.current?.abort()
  }, [execute, immediate])

  // 轮询
  useEffect(() => {
    if (!pollingInterval) return
    const id = setInterval(execute, pollingInterval)
    return () => clearInterval(id)
  }, [execute, pollingInterval])

  return { ...state, refetch: execute }
}

// 使用
function OrderStatus({ orderId }) {
  const { data: order, loading, error, refetch } = useFetch(
    `/api/orders/${orderId}`,
    {
      pollingInterval: 5000, // 每5秒轮询
      retryCount: 3,
      transform: data => ({
        ...data,
        createdAt: new Date(data.createdAt),
      }),
    }
  )

  if (loading && !order) return <Skeleton />
  if (error) return <Error message={error} onRetry={refetch} />
  return <OrderDetail order={order} />
}
```

---

## 6. 渲染与副作用机制（重点难点）

### 6.1 渲染 vs 副作用

|        | 渲染（Render）       | 副作用（Effect）             |
| ------ | -------------------- | ---------------------------- |
| 本质   | 纯函数，描述 UI      | 与外部系统交互               |
| 时机   | state/props 变化时   | 渲染完成后                   |
| 允许   | 计算、条件、JSX      | 请求、订阅、DOM操作、定时器  |
| 不允许 | 副作用（网络请求等） | 直接修改 state（会无限循环） |

```jsx
// ❌ 在渲染中执行副作用
function BadComponent() {
  const [data, setData] = useState(null)
  fetch('/api/data').then(r => r.json()).then(setData) // 每次渲染都请求！死循环！
  return <div>{data}</div>
}

// ✅ 副作用放在 useEffect 中
function GoodComponent() {
  const [data, setData] = useState(null)
  useEffect(() => {
    fetch('/api/data').then(r => r.json()).then(setData)
  }, [])
  return <div>{data}</div>
}
```

### 6.2 渲染快照机制

**每次渲染，所有 state 和 props 的值是那一次渲染独有的快照**，不会随后续更新变化：

```jsx
function MessageBoard() {
  const [message, setMessage] = useState('')
  const [history, setHistory] = useState([])

  function handleSendDelayed() {
    // 注意：这里的 message 是"这次渲染"时的值
    // 3秒后执行时，即使 message 已经被更新，这里打印的还是旧值
    setTimeout(() => {
      alert(`你发送了：${message}`)       // 快照值
      setHistory(prev => [...prev, message]) // 函数式更新获取最新值
    }, 3000)
  }

  return (
    <div>
      <input value={message} onChange={e => setMessage(e.target.value)} />
      <button onClick={handleSendDelayed}>3秒后发送</button>
    </div>
  )
}
// 操作步骤：
// 1. 输入 "Hello"
// 2. 点击发送
// 3. 立刻改成 "World"
// 4. 3秒后 alert 显示 "Hello"（快照），而不是 "World"
```

每次渲染的 effect 也绑定当次渲染的 state：

```jsx
function Counter() {
  const [count, setCount] = useState(0)

  useEffect(() => {
    // 这个 effect 属于 count=0 那次渲染
    // 即使后来 count 变成了 5，这里的 count 仍然是 0
    console.log(`effect: count = ${count}`)
  }, []) // 只执行一次，永远打印 0

  return <button onClick={() => setCount(c => c + 1)}>{count}</button>
}
```

### 6.3 闭包陷阱

快照机制导致的典型 bug——effect 或定时器中的值"过时"：

```jsx
// ❌ 经典闭包陷阱
function StaleCounter() {
  const [count, setCount] = useState(0)

  useEffect(() => {
    const id = setInterval(() => {
      setCount(count + 1) // count 永远是 0（闭包捕获了初始值）
    }, 1000)
    return () => clearInterval(id)
  }, []) // 依赖为空，effect 只运行一次，count 永远是快照值 0

  return <div>{count}</div> // 永远是 1！
}

// ✅ 解法1：函数式更新（不需要读取当前 count）
function FixedCounter1() {
  const [count, setCount] = useState(0)
  useEffect(() => {
    const id = setInterval(() => {
      setCount(c => c + 1) // 每次基于最新值 +1
    }, 1000)
    return () => clearInterval(id)
  }, [])
  return <div>{count}</div>
}

// ✅ 解法2：把依赖加入依赖数组（每次 count 变化都重新创建定时器）
function FixedCounter2() {
  const [count, setCount] = useState(0)
  useEffect(() => {
    const id = setInterval(() => {
      setCount(count + 1)
    }, 1000)
    return () => clearInterval(id) // 每次都清除旧定时器
  }, [count]) // 依赖 count
  return <div>{count}</div>
}

// ✅ 解法3：使用 useRef 存储最新值（见 useRef 章节的 useInterval）
```

### 6.4 依赖数组本质

依赖数组不是"性能优化"，是**同步机制**——告诉 React "这个 effect 需要和哪些值保持同步"：

```jsx
// 错误理解：我加依赖是为了控制执行次数
// 正确理解：我加依赖是因为 effect 的行为依赖这些值

// 例子：WebSocket 连接应该在 roomId 变化时重连
function ChatRoom({ roomId, userId }) {
  useEffect(() => {
    const ws = new WebSocket(`wss://chat.example.com/room/${roomId}`)

    ws.onopen = () => {
      ws.send(JSON.stringify({ type: 'join', userId }))
    }

    ws.onmessage = (event) => {
      const msg = JSON.parse(event.data)
      addMessage(msg)
    }

    return () => ws.close() // roomId 变化时关闭旧连接

  }, [roomId, userId]) // roomId 或 userId 变化都要重连
  // 如果写 []，换房间时不会重连，这是 bug！
}

// 依赖数组使用对象/数组时的陷阱（引用比较）
function SearchComponent({ config }) {
  useEffect(() => {
    doSearch(config)
  }, [config]) // ❌ config 是对象，每次父组件渲染都是新引用，effect 每次都执行！

  // ✅ 依赖具体的原始值
  useEffect(() => {
    doSearch(config)
  }, [config.keyword, config.pageSize, config.category])
}
```

### 6.5 批处理机制

React 18 以后，**所有地方**的 setState 都会自动批处理（包括 setTimeout、Promise、原生事件）：

```jsx
function BatchDemo() {
  const [count, setCount] = useState(0)
  const [flag, setFlag] = useState(false)

  function handleClick() {
    // React 18：以下三次 setState 只触发一次渲染
    setCount(c => c + 1)
    setCount(c => c + 1)
    setFlag(f => !f)
    // render 只执行一次！
  }

  async function handleAsync() {
    await someAPI()
    // React 18 之前：await 后的 setState 不会批处理，触发两次渲染
    // React 18 之后：自动批处理，只触发一次渲染
    setCount(c => c + 1)
    setFlag(f => !f)
  }

  // 如果需要强制立即渲染（不批处理）
  function handleImmediate() {
    flushSync(() => setCount(c => c + 1)) // 立即更新 DOM
    // 这里 DOM 已经更新了
    flushSync(() => setFlag(f => !f))
  }
}
```

---

## 7. 事件系统

### 7.1 React 事件模型

React 使用**合成事件（SyntheticEvent）**：

- 跨浏览器标准化（统一了 IE 等浏览器差异）
- **事件委托**：所有事件统一绑定到 React 根容器（React 17+ 是 root container，之前是 document），而非具体 DOM 节点
- 合成事件对象包装了原生事件，接口相同但行为统一

```
用户点击 button
  → 冒泡到 React 根容器
  → React 查找对应 Fiber 节点
  → 创建 SyntheticEvent 对象
  → 按冒泡顺序触发 onClick handler
```

### 7.2 事件绑定

```jsx
function InteractiveForm() {
  function handleSubmit(e) {
    e.preventDefault() // 阻止表单默认提交
    // 处理逻辑
  }

  function handleKeyDown(e) {
    if (e.key === 'Enter' && (e.ctrlKey || e.metaKey)) {
      handleSubmit(e) // Ctrl+Enter 提交
    }
    if (e.key === 'Escape') {
      resetForm()
    }
  }

  return (
    <form onSubmit={handleSubmit}>
      <textarea
        onKeyDown={handleKeyDown}
        onChange={e => setContent(e.target.value)}
        onPaste={e => handlePaste(e.clipboardData.getData('text'))}
        onDrop={e => {
          e.preventDefault()
          handleDrop(e.dataTransfer.files)
        }}
        onDragOver={e => e.preventDefault()}
      />
    </form>
  )
}
```

### 7.3 事件传参

```jsx
function OperationList({ operations }) {
  // ❌ 写法：每次渲染都创建新函数（小量时可接受）
  return operations.map(op => (
    <button key={op.id} onClick={() => handleOp(op.id, op.type)}>
      {op.label}
    </button>
  ))

  // ✅ 推荐：data 属性传参，减少函数创建
  function handleClick(e) {
    const { id, type } = e.currentTarget.dataset
    handleOp(id, type)
  }

  return operations.map(op => (
    <button
      key={op.id}
      data-id={op.id}
      data-type={op.type}
      onClick={handleClick}
    >
      {op.label}
    </button>
  ))
}
```

### 7.4 与原生事件区别

```jsx
function EventDemo() {
  const divRef = useRef()

  useEffect(() => {
    const div = divRef.current

    // 原生事件（捕获阶段）
    function nativeCapture(e) {
      console.log('native capture')
    }
    div.addEventListener('click', nativeCapture, true)

    // 原生事件（冒泡阶段）
    function nativeBubble(e) {
      console.log('native bubble')
    }
    div.addEventListener('click', nativeBubble)

    return () => {
      div.removeEventListener('click', nativeCapture, true)
      div.removeEventListener('click', nativeBubble)
    }
  }, [])

  // 点击内部 button，执行顺序（React 17+）：
  // 1. native capture (div)
  // 2. React onClick (button) - React 在 root 的捕获阶段模拟捕获
  // 3. React onClick (div)    - 冒泡
  // 4. native bubble (div)

  return (
    <div ref={divRef} onClick={() => console.log('react div')}>
      <button onClick={e => {
        e.stopPropagation()         // 阻止 React 合成事件冒泡
        e.nativeEvent.stopImmediatePropagation() // 阻止后续原生事件
        console.log('react button')
      }}>
        click
      </button>
    </div>
  )
}
```

**委托机制**：不要在 `document` 上绑定原生事件来监听 React 组件事件，因为 `e.stopPropagation()` 只阻止合成事件冒泡，原生事件仍会到达 document。

---

## 8. 表单系统

### 8.1 受控组件

React 控制 input 的值，value 始终与 state 同步：

```jsx
function RegistrationForm() {
  const [form, setForm] = useState({
    username: '',
    email: '',
    password: '',
    confirmPassword: '',
    role: 'user',
    newsletter: false,
    bio: '',
  })
  const [errors, setErrors] = useState({})

  function handleChange(e) {
    const { name, value, type, checked } = e.target
    setForm(prev => ({
      ...prev,
      [name]: type === 'checkbox' ? checked : value,
    }))
    // 实时清除错误
    setErrors(prev => ({ ...prev, [name]: '' }))
  }

  function validate() {
    const newErrors = {}
    if (!form.username.trim()) newErrors.username = '用户名不能为空'
    else if (form.username.length < 3) newErrors.username = '用户名至少3位'
    if (!/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(form.email)) newErrors.email = '邮箱格式不正确'
    if (form.password.length < 8) newErrors.password = '密码至少8位'
    if (form.password !== form.confirmPassword) newErrors.confirmPassword = '两次密码不一致'
    return newErrors
  }

  function handleSubmit(e) {
    e.preventDefault()
    const newErrors = validate()
    if (Object.keys(newErrors).length > 0) {
      setErrors(newErrors)
      return
    }
    submitForm(form)
  }

  return (
    <form onSubmit={handleSubmit} noValidate>
      <Field label="用户名" error={errors.username}>
        <input name="username" value={form.username} onChange={handleChange} />
      </Field>

      <Field label="邮箱" error={errors.email}>
        <input type="email" name="email" value={form.email} onChange={handleChange} />
      </Field>

      <Field label="密码" error={errors.password}>
        <input type="password" name="password" value={form.password} onChange={handleChange} />
      </Field>

      <Field label="确认密码" error={errors.confirmPassword}>
        <input type="password" name="confirmPassword" value={form.confirmPassword} onChange={handleChange} />
      </Field>

      <Field label="角色">
        <select name="role" value={form.role} onChange={handleChange}>
          <option value="user">普通用户</option>
          <option value="editor">编辑</option>
          <option value="admin">管理员</option>
        </select>
      </Field>

      <label>
        <input type="checkbox" name="newsletter" checked={form.newsletter} onChange={handleChange} />
        订阅邮件通知
      </label>

      <Field label="个人简介">
        <textarea name="bio" value={form.bio} onChange={handleChange} maxLength={200} />
        <span>{form.bio.length}/200</span>
      </Field>

      <button type="submit">注册</button>
    </form>
  )
}
```

### 8.2 非受控组件

由 DOM 自己管理值，通过 ref 在需要时读取：

```jsx
function FileUploadForm() {
  const fileRef = useRef(null)
  const nameRef = useRef(null)

  function handleSubmit(e) {
    e.preventDefault()
    const name = nameRef.current.value
    const files = fileRef.current.files

    if (!name || !files.length) return

    const formData = new FormData()
    formData.append('name', name)
    Array.from(files).forEach(file => formData.append('files', file))

    uploadAPI(formData)
  }

  // 非受控适用场景：
  // - 文件上传（file input 只能非受控）
  // - 与第三方非 React 库集成
  // - 不需要实时验证的简单表单

  return (
    <form onSubmit={handleSubmit}>
      <input ref={nameRef} type="text" defaultValue="" placeholder="文件名" />
      <input ref={fileRef} type="file" multiple accept="image/*,.pdf" />
      <button type="submit">上传</button>
    </form>
  )
}
```

### 8.3 表单状态管理

复杂表单推荐使用 React Hook Form：

```jsx
import { useForm, Controller } from 'react-hook-form'
import { zodResolver } from '@hookform/resolvers/zod'
import { z } from 'zod'

const schema = z.object({
  title: z.string().min(1, '标题不能为空').max(100),
  content: z.string().min(10, '内容至少10字'),
  tags: z.array(z.string()).min(1, '至少选一个标签'),
  publishAt: z.date().min(new Date(), '发布时间不能是过去'),
  visibility: z.enum(['public', 'private', 'draft']),
})

function ArticleEditor({ initialData, onSave }) {
  const {
    register,
    control,
    handleSubmit,
    watch,
    formState: { errors, isDirty, isSubmitting },
  } = useForm({
    resolver: zodResolver(schema),
    defaultValues: initialData,
  })

  const content = watch('content', '')

  return (
    <form onSubmit={handleSubmit(onSave)}>
      <input {...register('title')} placeholder="文章标题" />
      {errors.title && <p className="error">{errors.title.message}</p>}

      <textarea {...register('content')} rows={20} />
      <span>{content.length} 字</span>
      {errors.content && <p className="error">{errors.content.message}</p>}

      <Controller
        name="tags"
        control={control}
        render={({ field }) => (
          <TagSelector value={field.value} onChange={field.onChange} />
        )}
      />

      <Controller
        name="publishAt"
        control={control}
        render={({ field }) => (
          <DateTimePicker value={field.value} onChange={field.onChange} />
        )}
      />

      <select {...register('visibility')}>
        <option value="draft">草稿</option>
        <option value="public">公开</option>
        <option value="private">私密</option>
      </select>

      <button type="submit" disabled={!isDirty || isSubmitting}>
        {isSubmitting ? '保存中...' : '保存'}
      </button>
    </form>
  )
}
```

---

## 9. 样式系统

### 9.1 className

```jsx
// 动态 className
import clsx from 'clsx' // 或 classnames 库

function Button({ variant = 'primary', size = 'md', loading, disabled, className, children }) {
  return (
    <button
      className={clsx(
        'btn',
        `btn--${variant}`,
        `btn--${size}`,
        loading && 'btn--loading',
        disabled && 'btn--disabled',
        className
      )}
      disabled={disabled || loading}
    >
      {loading && <Spinner size="sm" />}
      {children}
    </button>
  )
}
```

### 9.2 inline style

```jsx
// 适合动态计算的样式值
function ProgressBar({ value, max = 100, color = '#3b82f6' }) {
  const percent = Math.min(100, Math.max(0, (value / max) * 100))
  return (
    <div className="progress-track">
      <div
        className="progress-fill"
        style={{
          width: `${percent}%`,
          backgroundColor: color,
          transition: 'width 0.3s ease',
        }}
        role="progressbar"
        aria-valuenow={value}
        aria-valuemax={max}
      />
    </div>
  )
}

// CSS 变量 + inline style 组合
function ThemedCard({ primaryColor, children }) {
  return (
    <div
      className="themed-card"
      style={{ '--primary': primaryColor }} // 设置 CSS 变量
    >
      {children}
      {/* CSS 里用 var(--primary) 引用 */}
    </div>
  )
}
```

### 9.3 CSS Modules

```jsx
// Button.module.css
/*
.button { padding: 8px 16px; }
.primary { background: #3b82f6; color: white; }
.danger { background: #ef4444; color: white; }
.loading { opacity: 0.7; cursor: not-allowed; }
*/

import styles from './Button.module.css'
import clsx from 'clsx'

function Button({ variant = 'primary', loading, children }) {
  return (
    <button className={clsx(styles.button, styles[variant], loading && styles.loading)}>
      {children}
    </button>
  )
}
// 编译后 className 变成 Button_button__abc123，自动避免命名冲突
```

### 9.4 CSS-in-JS

以 styled-components 为例：

```jsx
import styled, { css, keyframes } from 'styled-components'

const pulse = keyframes`
  0%, 100% { opacity: 1; }
  50% { opacity: 0.5; }
`

const Card = styled.div`
  background: ${props => props.theme.colors.surface};
  border-radius: 12px;
  box-shadow: 0 2px 8px rgba(0,0,0,0.1);
  padding: 24px;
  transition: box-shadow 0.2s;

  &:hover {
    box-shadow: 0 4px 16px rgba(0,0,0,0.15);
  }

  ${props => props.loading && css`
    animation: ${pulse} 1.5s ease-in-out infinite;
    pointer-events: none;
  `}
`

const Title = styled.h2`
  font-size: clamp(1rem, 2.5vw, 1.5rem);
  color: ${props => props.theme.colors.text.primary};
  margin: 0 0 16px;
`

function ArticleCard({ article, loading }) {
  return (
    <Card loading={loading}>
      <Title>{article.title}</Title>
      <p>{article.summary}</p>
    </Card>
  )
}
```

### 9.5 UI 库

常用 UI 库对比：

| 库           | 特点                   | 适用          |
| ------------ | ---------------------- | ------------- |
| Ant Design   | 企业级，功能全         | 后台管理系统  |
| Material UI  | Google Material Design | 通用 Web 应用 |
| shadcn/ui    | 无样式组件，可定制     | 高定制需求    |
| Tailwind CSS | 原子化 CSS             | 快速开发      |
| Headless UI  | 无样式，只提供行为     | 配合 Tailwind |

---

## 10. 路由系统

### 10.1 SPA 概念

单页应用（SPA）：只加载一次 HTML，路由切换由 JS 控制（不刷新页面）。

- **Hash 路由**：`/#/about` — 兼容性好，不需要服务端配置
- **History 路由**：`/about` — 需要服务端配置（所有路径返回 index.html）

### 10.2 React Router

```jsx
import {
  createBrowserRouter,
  RouterProvider,
  Outlet,
  Link,
  NavLink,
  useNavigate,
  useParams,
  useSearchParams,
  useLocation,
  Navigate,
} from 'react-router-dom'

const router = createBrowserRouter([
  {
    path: '/',
    element: <RootLayout />,
    errorElement: <ErrorPage />,
    children: [
      { index: true, element: <HomePage /> },
      {
        path: 'products',
        element: <ProductsLayout />,
        children: [
          { index: true, element: <ProductList /> },
          { path: ':id', element: <ProductDetail /> },
          { path: ':id/reviews', element: <ProductReviews /> },
        ],
      },
      {
        path: 'dashboard',
        element: <ProtectedRoute><DashboardLayout /></ProtectedRoute>,
        children: [
          { index: true, element: <Overview /> },
          { path: 'orders', element: <Orders /> },
          { path: 'settings', element: <Settings /> },
        ],
      },
      { path: 'login', element: <Login /> },
      { path: '*', element: <NotFound /> },
    ],
  },
])

function App() {
  return <RouterProvider router={router} />
}
```

### 10.3 路由参数

```jsx
// URL: /products/123?color=red&size=L
function ProductDetail() {
  const { id } = useParams()                          // 路径参数
  const [searchParams, setSearchParams] = useSearchParams() // 查询参数
  const location = useLocation()                      // 完整 location 对象
  const navigate = useNavigate()

  const color = searchParams.get('color') || 'default'
  const size = searchParams.get('size') || 'M'

  function handleColorChange(newColor) {
    setSearchParams(prev => {
      prev.set('color', newColor)
      return prev
    })
  }

  function handleAddToCart() {
    navigate('/cart', {
      state: { from: location.pathname, product: { id, color, size } }
    })
  }

  return (
    <div>
      <h1>Product {id}</h1>
      <ColorPicker value={color} onChange={handleColorChange} />
      <button onClick={handleAddToCart}>加入购物车</button>
      <button onClick={() => navigate(-1)}>返回</button>
    </div>
  )
}
```

### 10.4 嵌套路由

```jsx
// 嵌套路由的关键：Outlet 渲染子路由
function DashboardLayout() {
  const { user } = useAuth()

  return (
    <div className="dashboard">
      <aside>
        <NavLink to="/dashboard" end className={({ isActive }) => isActive ? 'active' : ''}>
          概览
        </NavLink>
        <NavLink to="/dashboard/orders" className={({ isActive }) => isActive ? 'active' : ''}>
          订单管理
        </NavLink>
        {user.isAdmin && (
          <NavLink to="/dashboard/settings" className={({ isActive }) => isActive ? 'active' : ''}>
            系统设置
          </NavLink>
        )}
      </aside>
      <main>
        <Outlet /> {/* 子路由渲染位置 */}
      </main>
    </div>
  )
}

// 权限路由
function ProtectedRoute({ children, requiredRole }) {
  const { user } = useAuth()
  const location = useLocation()

  if (!user) {
    return <Navigate to="/login" state={{ from: location }} replace />
  }

  if (requiredRole && user.role !== requiredRole) {
    return <Navigate to="/403" replace />
  }

  return children
}
```

---

## 11. 状态管理体系（全局）

### 11.1 为什么需要

当多个组件需要共享状态，且这些组件不在同一个父子链上，Context 或 props drilling 不够用时。

### 11.2 方案对比

| 方案           | 适用场景                   | 复杂度 |
| -------------- | -------------------------- | ------ |
| props          | 父子通信                   | 低     |
| Context        | 跨层共享（主题、用户信息） | 低     |
| Zustand        | 中小型应用，轻量全局状态   | 低     |
| Redux Toolkit  | 大型应用，复杂状态逻辑     | 中     |
| Jotai / Recoil | 原子化状态，细粒度订阅     | 中     |
| React Query    | 服务端状态（缓存、同步）   | 低     |

### 11.3 Redux 核心

```jsx
// Redux Toolkit（现代 Redux 写法）
import { createSlice, createAsyncThunk, configureStore } from '@reduxjs/toolkit'

// Async Thunk
const fetchProducts = createAsyncThunk(
  'products/fetchAll',
  async (params, { rejectWithValue }) => {
    try {
      const response = await productAPI.getList(params)
      return response.data
    } catch (err) {
      return rejectWithValue(err.response.data)
    }
  }
)

// Slice（包含 reducer + actions）
const productsSlice = createSlice({
  name: 'products',
  initialState: {
    items: [],
    total: 0,
    loading: false,
    error: null,
    filters: { category: '', priceRange: [0, 99999] },
    page: 1,
  },
  reducers: {
    setFilters(state, action) {
      state.filters = { ...state.filters, ...action.payload }
      state.page = 1
    },
    setPage(state, action) {
      state.page = action.payload
    },
    updateProductStock(state, action) {
      const product = state.items.find(p => p.id === action.payload.id)
      if (product) product.stock = action.payload.stock
    },
  },
  extraReducers: (builder) => {
    builder
      .addCase(fetchProducts.pending, (state) => {
        state.loading = true
        state.error = null
      })
      .addCase(fetchProducts.fulfilled, (state, action) => {
        state.loading = false
        state.items = action.payload.items
        state.total = action.payload.total
      })
      .addCase(fetchProducts.rejected, (state, action) => {
        state.loading = false
        state.error = action.payload?.message || '加载失败'
      })
  },
})

// Store
const store = configureStore({
  reducer: {
    products: productsSlice.reducer,
    cart: cartSlice.reducer,
    user: userSlice.reducer,
  },
})

// 使用
function ProductListPage() {
  const dispatch = useDispatch()
  const { items, loading, error, filters, page } = useSelector(state => state.products)

  useEffect(() => {
    dispatch(fetchProducts({ ...filters, page }))
  }, [dispatch, filters, page])

  return (
    <div>
      <FilterBar filters={filters} onChange={f => dispatch(setFilters(f))} />
      {loading && <Spinner />}
      {error && <Error message={error} />}
      <ProductGrid items={items} />
      <Pagination page={page} onChange={p => dispatch(setPage(p))} total={total} />
    </div>
  )
}
```

---

## 12. 性能优化体系

### 12.1 渲染优化

**原则**：先测量，再优化。不要过早优化。

```jsx
// 优化链：
// 1. memo 阻止不必要的子组件渲染
// 2. useCallback 稳定函数引用
// 3. useMemo 缓存计算结果

// 典型场景：大型列表 + 频繁父组件更新
function Dashboard() {
  const [ticker, setTicker] = useState(0)
  const [data] = useState(() => generateLargeDataset())

  // 父组件每秒更新，但子组件不需要跟着更新
  useEffect(() => {
    const id = setInterval(() => setTicker(t => t + 1), 1000)
    return () => clearInterval(id)
  }, [])

  const processedData = useMemo(() => expensiveProcess(data), [data])
  const handleRowClick = useCallback((id) => { navigate(`/item/${id}`) }, [navigate])
  const handleSort = useCallback((col) => { setSortCol(col) }, [])

  return (
    <div>
      <Clock tick={ticker} /> {/* 每秒更新 */}
      <DataTable           {/* 不受 ticker 影响 */}
        data={processedData}
        onRowClick={handleRowClick}
        onSort={handleSort}
      />
    </div>
  )
}

const DataTable = memo(function DataTable({ data, onRowClick, onSort }) {
  // 只在 data/onRowClick/onSort 变化时渲染
  return (
    <table>
      {data.map(row => (
        <DataRow key={row.id} row={row} onClick={onRowClick} />
      ))}
    </table>
  )
})

const DataRow = memo(function DataRow({ row, onClick }) {
  return <tr onClick={() => onClick(row.id)}>...</tr>
})
```

### 12.2 结构优化

**状态下沉**：将状态移到真正需要它的最小组件内，减少影响范围：

```jsx
// ❌ 搜索框的状态放在父组件，每次输入触发整个 ProductPage 重渲染
function ProductPage() {
  const [searchQuery, setSearchQuery] = useState('')
  return (
    <div>
      <SearchInput value={searchQuery} onChange={setSearchQuery} />
      <ExpensiveProductGrid /> {/* 不需要 searchQuery 却每次都重渲染 */}
    </div>
  )
}

// ✅ 状态下沉到 SearchInput 内部（如果其他组件不需要的话）
function ProductPage() {
  return (
    <div>
      <SearchInput onSearch={handleSearch} /> {/* 内部管理输入状态 */}
      <ExpensiveProductGrid />                 {/* 不再重渲染 */}
    </div>
  )
}

// 或：将"受影响的组件"下沉到一起
function SearchSection() {
  const [query, setQuery] = useState('')
  return (
    <>
      <SearchInput value={query} onChange={setQuery} />
      <SearchResults query={query} />  {/* 只有这些组件受影响 */}
    </>
  )
}
```

### 12.3 列表优化

**key**：

```jsx
// ❌ 用 index 作 key：删除中间元素时，后面元素的 key 变了，触发不必要的重建
{items.map((item, i) => <Input key={i} defaultValue={item.text} />)}

// ✅ 稳定唯一 ID
{items.map(item => <Input key={item.id} defaultValue={item.text} />)}
```

**虚拟列表**（处理上千条数据）：

```jsx
import { FixedSizeList, VariableSizeList } from 'react-window'
import AutoSizer from 'react-virtualized-auto-sizer'

function VirtualTable({ items }) {
  const Row = memo(({ index, style }) => {
    const item = items[index]
    return (
      <div style={style} className="row">
        <span>{item.name}</span>
        <span>{item.value}</span>
      </div>
    )
  })

  return (
    <AutoSizer>
      {({ height, width }) => (
        <FixedSizeList
          height={height}
          width={width}
          itemCount={items.length}
          itemSize={48}  // 每行高度
          overscanCount={5}
        >
          {Row}
        </FixedSizeList>
      )}
    </AutoSizer>
  )
}
```

---

## 13. 工程化体系

### 13.1 项目结构设计

```
src/
├── app/                    # 应用入口、全局配置
│   ├── store.ts
│   ├── router.tsx
│   └── App.tsx
├── pages/                  # 路由页面
│   ├── home/
│   │   ├── index.tsx
│   │   └── components/    # 页面私有组件
│   └── product/
├── features/               # 功能模块（按业务划分）
│   ├── auth/
│   │   ├── authSlice.ts
│   │   ├── AuthContext.tsx
│   │   ├── useAuth.ts
│   │   └── LoginForm.tsx
│   └── cart/
├── components/             # 通用 UI 组件
│   ├── Button/
│   │   ├── Button.tsx
│   │   ├── Button.module.css
│   │   ├── Button.test.tsx
│   │   └── index.ts
│   └── Modal/
├── hooks/                  # 通用自定义 Hooks
│   ├── useDebounce.ts
│   ├── useLocalStorage.ts
│   └── useMediaQuery.ts
├── services/               # API 请求
│   ├── api.ts             # axios 实例配置
│   ├── productService.ts
│   └── orderService.ts
├── utils/                  # 纯函数工具
├── types/                  # TypeScript 类型定义
└── constants/              # 常量
```

### 13.2 代码规范（ESLint / Prettier）

```json
// .eslintrc.json
{
  "extends": [
    "eslint:recommended",
    "plugin:react/recommended",
    "plugin:react-hooks/recommended",
    "plugin:@typescript-eslint/recommended",
    "prettier"
  ],
  "rules": {
    "react-hooks/exhaustive-deps": "error",  // 依赖数组必须完整
    "react/prop-types": "off",               // TypeScript 项目关闭
    "no-console": ["warn", { "allow": ["warn", "error"] }]
  }
}
```

### 13.3 API 管理

```ts
// services/api.ts — axios 实例
import axios from 'axios'

const api = axios.create({
  baseURL: import.meta.env.VITE_API_BASE_URL,
  timeout: 10000,
})

// 请求拦截：注入 token
api.interceptors.request.use(config => {
  const token = localStorage.getItem('token')
  if (token) config.headers.Authorization = `Bearer ${token}`
  return config
})

// 响应拦截：统一错误处理
api.interceptors.response.use(
  response => response.data,
  error => {
    if (error.response?.status === 401) {
      localStorage.removeItem('token')
      window.location.href = '/login'
    }
    return Promise.reject(error.response?.data || error)
  }
)

export default api

// services/productService.ts
export const productService = {
  getList: (params) => api.get('/products', { params }),
  getById: (id) => api.get(`/products/${id}`),
  create: (data) => api.post('/products', data),
  update: (id, data) => api.put(`/products/${id}`, data),
  delete: (id) => api.delete(`/products/${id}`),
}
```

### 13.4 环境变量

```bash
# .env.development
VITE_API_BASE_URL=http://localhost:3000/api
VITE_APP_TITLE=My App (Dev)

# .env.production
VITE_API_BASE_URL=https://api.example.com
VITE_APP_TITLE=My App
```

```ts
// 使用（Vite 项目）
const baseURL = import.meta.env.VITE_API_BASE_URL
// Create React App 项目用 process.env.REACT_APP_API_URL
```

### 13.5 组件设计模式

```tsx
// 复合组件（Compound Components）模式
// 允许使用方控制内部结构
interface SelectContextType {
  value: string
  onChange: (value: string) => void
}
const SelectContext = createContext<SelectContextType | null>(null)

function Select({ value, onChange, children }) {
  return (
    <SelectContext.Provider value={{ value, onChange }}>
      <div className="select">{children}</div>
    </SelectContext.Provider>
  )
}

Select.Trigger = function Trigger({ children }) {
  const { value } = useContext(SelectContext)!
  return <button className="select-trigger">{value || children}</button>
}

Select.Options = function Options({ children }) {
  return <ul className="select-options">{children}</ul>
}

Select.Option = function Option({ value, children }) {
  const ctx = useContext(SelectContext)!
  return (
    <li
      className={ctx.value === value ? 'selected' : ''}
      onClick={() => ctx.onChange(value)}
    >
      {children}
    </li>
  )
}

// 使用
<Select value={selected} onChange={setSelected}>
  <Select.Trigger>请选择</Select.Trigger>
  <Select.Options>
    <Select.Option value="react">React</Select.Option>
    <Select.Option value="vue">Vue</Select.Option>
  </Select.Options>
</Select>
```

---

## 14. TypeScript + React

### 14.1 Props 类型

```tsx
// 基础 Props 类型
interface ButtonProps {
  variant?: 'primary' | 'secondary' | 'danger'
  size?: 'sm' | 'md' | 'lg'
  loading?: boolean
  disabled?: boolean
  onClick?: (event: React.MouseEvent<HTMLButtonElement>) => void
  children: React.ReactNode
  className?: string
}

// 扩展原生 HTML 元素属性
interface InputProps extends React.InputHTMLAttributes<HTMLInputElement> {
  label?: string
  error?: string
  helperText?: string
}

function Input({ label, error, helperText, className, ...inputProps }: InputProps) {
  return (
    <div className={clsx('field', error && 'field--error', className)}>
      {label && <label>{label}</label>}
      <input {...inputProps} />
      {error && <span className="error">{error}</span>}
      {helperText && <span className="helper">{helperText}</span>}
    </div>
  )
}

// 多态组件（as prop）
type PolymorphicProps<C extends React.ElementType, Props = {}> = Props &
  Omit<React.ComponentPropsWithRef<C>, keyof Props> & { as?: C }

function Text<C extends React.ElementType = 'span'>({
  as,
  children,
  ...props
}: PolymorphicProps<C, { children: React.ReactNode }>) {
  const Component = as || 'span'
  return <Component {...props}>{children}</Component>
}

// 使用
<Text as="h1" className="title">标题</Text>   // 渲染为 h1
<Text as="p" className="body">段落</Text>    // 渲染为 p
<Text as={Link} to="/about">链接</Text>      // 渲染为 Link
```

### 14.2 Hooks 类型

```tsx
// useState 类型推断
const [count, setCount] = useState(0)                    // number
const [user, setUser] = useState<User | null>(null)      // 需要显式指定
const [items, setItems] = useState<Product[]>([])        // 显式指定

// useRef 类型
const inputRef = useRef<HTMLInputElement>(null)           // DOM 引用：可能为 null
const timerRef = useRef<ReturnType<typeof setTimeout>>() // 定时器 ID
const countRef = useRef<number>(0)                       // 可变值：不为 null

// useReducer 类型
type State = {
  status: 'idle' | 'loading' | 'success' | 'error'
  data: Product[] | null
  error: string | null
}

type Action =
  | { type: 'FETCH_START' }
  | { type: 'FETCH_SUCCESS'; payload: Product[] }
  | { type: 'FETCH_ERROR'; payload: string }

function reducer(state: State, action: Action): State {
  switch (action.type) {
    case 'FETCH_START': return { ...state, status: 'loading', error: null }
    case 'FETCH_SUCCESS': return { status: 'success', data: action.payload, error: null }
    case 'FETCH_ERROR': return { ...state, status: 'error', error: action.payload }
  }
}
```

### 14.3 事件类型

```tsx
function Form() {
  function handleChange(e: React.ChangeEvent<HTMLInputElement>) {
    const { name, value } = e.target
  }

  function handleSelectChange(e: React.ChangeEvent<HTMLSelectElement>) {
    const value = e.target.value
  }

  function handleSubmit(e: React.FormEvent<HTMLFormElement>) {
    e.preventDefault()
    const formData = new FormData(e.currentTarget)
  }

  function handleKeyDown(e: React.KeyboardEvent<HTMLTextAreaElement>) {
    if (e.key === 'Enter' && e.ctrlKey) handleSubmit(e as any)
  }

  function handleDrop(e: React.DragEvent<HTMLDivElement>) {
    const files = Array.from(e.dataTransfer.files)
  }

  function handleClick(e: React.MouseEvent<HTMLButtonElement>) {
    e.currentTarget.blur()
  }
}
```

### 14.4 泛型组件

```tsx
// 泛型列表组件
interface ListProps<T> {
  items: T[]
  getKey: (item: T) => string | number
  renderItem: (item: T, index: number) => React.ReactNode
  renderEmpty?: () => React.ReactNode
  loading?: boolean
}

function List<T>({ items, getKey, renderItem, renderEmpty, loading }: ListProps<T>) {
  if (loading) return <Skeleton count={3} />
  if (items.length === 0) return <>{renderEmpty?.() ?? <EmptyState />}</>
  return (
    <ul>
      {items.map((item, i) => (
        <li key={getKey(item)}>{renderItem(item, i)}</li>
      ))}
    </ul>
  )
}

// 类型安全的使用
<List<Product>
  items={products}
  getKey={p => p.id}
  renderItem={p => <ProductCard product={p} />}
/>

// 泛型 Select
interface SelectProps<T extends { id: string | number; label: string }> {
  options: T[]
  value: T | null
  onChange: (value: T) => void
  getLabel?: (option: T) => string
}

function Select<T extends { id: string | number; label: string }>({
  options, value, onChange, getLabel = o => o.label,
}: SelectProps<T>) {
  return (
    <select value={value?.id ?? ''} onChange={e => {
      const found = options.find(o => String(o.id) === e.target.value)
      if (found) onChange(found)
    }}>
      {options.map(opt => (
        <option key={opt.id} value={opt.id}>{getLabel(opt)}</option>
      ))}
    </select>
  )
}
```

---

## 15. React 原理体系

### 15.1 虚拟 DOM

虚拟 DOM 是轻量的 JS 对象树，描述 UI 结构。React 先更新虚拟 DOM，再通过 Diff 算法计算最小变更，最后批量更新真实 DOM：

```
真实 DOM 操作昂贵（涉及布局计算、重绘）
  → 用 JS 对象（虚拟 DOM）描述 UI
  → JS 对象操作廉价
  → diff 算法计算最小变更
  → 一次性批量更新真实 DOM
```

**注意**：虚拟 DOM 的优势不是"比直接操作 DOM 快"，而是让开发者用声明式代码（不必手动操作 DOM），同时 React 保证"足够高效"。

### 15.2 Diff 算法

React 的 Diff 基于三个假设，将 O(n³) 降到 O(n)：

1. **不同类型节点**直接替换（不复用）
2. **key** 用于识别列表中的节点
3. **同层比较**（不跨层移动）

```jsx
// 类型变化：直接卸载旧组件，挂载新组件（状态丢失）
// 之前：<Counter />
// 之后：<p>123</p>
// Counter 的 state 全部丢失

// key 的作用：让 React 识别出是"同一个"元素
// 没有 key：
// 旧: [A, B, C]
// 新: [X, A, B, C]
// React 以为 A 变成了 X，B 变成了 A... 全部更新，效率低

// 有 key：
// React 识别出 X 是新增，A/B/C 只需移动，高效

// 利用 key 强制重置组件状态
function ProfilePage({ userId }) {
  return (
    <UserProfile
      key={userId}  // userId 变化时，强制卸载重挂载（state 重置）
      userId={userId}
    />
  )
}
```

### 15.3 Fiber

Fiber 是 React 16 引入的新协调架构：

- **可中断**：Fiber 将渲染工作拆分成小单元，可以暂停、恢复（让出主线程给浏览器）
- **优先级调度**：高优先级更新（用户输入）可以打断低优先级更新（数据渲染）
- **双缓存**：current tree（当前 DOM）+ workInProgress tree（正在构建），完成后切换

```
传统 Stack Reconciler（React 15）：
  同步递归，一旦开始无法中断 → 长任务阻塞 UI → 卡顿

Fiber Reconciler（React 16+）：
  工作单元（Fiber 节点）→ 循环处理（非递归）
  → 每处理一个 Fiber，检查是否需要让出 → 浏览器响应输入 → 恢复工作
```

### 15.4 调度机制（概念级）

```
React Scheduler 按优先级调度更新：

- ImmediatePriority（同步）：如 flushSync
- UserBlockingPriority（16ms）：用户输入（点击、输入）
- NormalPriority（250ms）：普通更新
- LowPriority（1000ms）：过渡动画（useTransition）
- IdlePriority：后台预渲染

useTransition 示例：
function TabSwitcher() {
  const [tab, setTab] = useState('home')
  const [isPending, startTransition] = useTransition()

  function handleTabClick(newTab) {
    startTransition(() => {
      setTab(newTab)  // 标记为低优先级，用户输入不会被阻塞
    })
  }

  return (
    <div>
      <TabBar onTabClick={handleTabClick} />
      {isPending && <Spinner />}
      <TabContent tab={tab} />  {/* 内容更新可以被中断 */}
    </div>
  )
}
```

---

## 16. 进阶模式

### 16.1 高阶组件（HOC）

HOC（Higher-Order Component） 是一个接受组件、返回增强组件的函数：

```jsx
// 权限控制 HOC
function withPermission(WrappedComponent, requiredPermission) {
  return function PermissionGuard(props) {
    const { user } = useAuth()
    const hasPermission = user?.permissions?.includes(requiredPermission)

    if (!hasPermission) {
      return <Forbidden message={`需要 ${requiredPermission} 权限`} />
    }

    return <WrappedComponent {...props} />
  }
}

// 加载状态 HOC
function withLoadingState(WrappedComponent) {
  return function WithLoading({ isLoading, loadingFallback = <Spinner />, ...props }) {
    if (isLoading) return loadingFallback
    return <WrappedComponent {...props} />
  }
}

// 日志 HOC
function withPerformanceTracking(WrappedComponent, componentName) {
  return function Tracked(props) {
    const renderCount = useRef(0)
    renderCount.current++

    useEffect(() => {
      const start = performance.now()
      return () => {
        console.log(`${componentName} 第 ${renderCount.current} 次渲染耗时: ${performance.now() - start}ms`)
      }
    })

    return <WrappedComponent {...props} />
  }
}

// 使用（HOC 组合）
const AdminPanel = withPermission(
  withLoadingState(
    withPerformanceTracking(PanelComponent, 'AdminPanel')
  ),
  'admin:read'
)
```

### 16.2 Render Props

通过 prop 传入函数来共享状态逻辑：

```jsx
// 复杂 Render Props：鼠标追踪 + 碰撞检测
function DraggableArea({ onCollision, render }) {
  const [position, setPosition] = useState({ x: 0, y: 0 })
  const [isDragging, setIsDragging] = useState(false)
  const areaRef = useRef()

  function handleMouseMove(e) {
    if (!isDragging) return
    const rect = areaRef.current.getBoundingClientRect()
    const x = e.clientX - rect.left
    const y = e.clientY - rect.top

    setPosition({ x, y })

    // 检测碰撞
    const targets = areaRef.current.querySelectorAll('[data-droptarget]')
    targets.forEach(target => {
      const targetRect = target.getBoundingClientRect()
      const relRect = { ...targetRect, left: targetRect.left - rect.left, top: targetRect.top - rect.top }
      const isOver = x >= relRect.left && x <= relRect.left + relRect.width
                  && y >= relRect.top  && y <= relRect.top  + relRect.height
      if (isOver) onCollision?.(target.dataset.droptarget)
    })
  }

  return (
    <div ref={areaRef} onMouseMove={handleMouseMove} onMouseUp={() => setIsDragging(false)}>
      {render({ position, isDragging, startDragging: () => setIsDragging(true) })}
    </div>
  )
}

// 使用
<DraggableArea
  onCollision={targetId => handleDrop(targetId)}
  render={({ position, isDragging, startDragging }) => (
    <div>
      <div
        style={{ position: 'absolute', left: position.x, top: position.y, cursor: isDragging ? 'grabbing' : 'grab' }}
        onMouseDown={startDragging}
      >
        拖我
      </div>
      <div data-droptarget="zone1" className="drop-zone">放这里</div>
    </div>
  )}
/>
```

### 16.3 Compound Components

见 13.5 示例。核心：父组件通过 Context 共享状态，子组件通过 Context 消费。

### 16.4 Portals

将子组件渲染到 DOM 树中任意位置（跳出父组件的 overflow/z-index 限制）：

```jsx
import { createPortal } from 'react-dom'

function Modal({ isOpen, onClose, title, children, size = 'md' }) {
  useEffect(() => {
    if (!isOpen) return
    const originalOverflow = document.body.style.overflow
    document.body.style.overflow = 'hidden' // 禁止背景滚动

    function handleEsc(e) {
      if (e.key === 'Escape') onClose()
    }
    document.addEventListener('keydown', handleEsc)

    return () => {
      document.body.style.overflow = originalOverflow
      document.removeEventListener('keydown', handleEsc)
    }
  }, [isOpen, onClose])

  if (!isOpen) return null

  // 渲染到 body 下，不受父组件 CSS 影响
  return createPortal(
    <div className="modal-backdrop" onClick={onClose}>
      <div
        className={`modal modal--${size}`}
        onClick={e => e.stopPropagation()} // 点击内部不关闭
        role="dialog"
        aria-modal="true"
        aria-labelledby="modal-title"
      >
        <header>
          <h2 id="modal-title">{title}</h2>
          <button onClick={onClose} aria-label="关闭">×</button>
        </header>
        <div className="modal-body">{children}</div>
      </div>
    </div>,
    document.body
  )
}
```

### 16.5 Suspense / lazy

代码分割 + 懒加载：

```jsx
import { lazy, Suspense } from 'react'

// 路由级代码分割
const ProductList = lazy(() => import('./pages/ProductList'))
const ProductDetail = lazy(() => import('./pages/ProductDetail'))
const AdminDashboard = lazy(() =>
  import('./pages/AdminDashboard').then(module => ({
    default: module.AdminDashboard // 具名导出时
  }))
)

// 全局 Loading 边界
function AppRouter() {
  return (
    <Suspense fallback={<PageSkeleton />}>
      <Routes>
        <Route path="/products" element={<ProductList />} />
        <Route path="/products/:id" element={<ProductDetail />} />
        <Route path="/admin" element={<AdminDashboard />} />
      </Routes>
    </Suspense>
  )
}

// 组件级 Suspense（React 18 数据请求）
function ProductPage({ id }) {
  return (
    <div>
      <Suspense fallback={<ProductInfoSkeleton />}>
        <ProductInfo id={id} />      {/* 内部用 use() 或 Suspense-aware 库 */}
      </Suspense>
      <Suspense fallback={<ReviewsSkeleton />}>
        <ReviewSection productId={id} />
      </Suspense>
    </div>
  )
}
```

---

## 17. 数据请求体系

### 17.1 fetch / axios

```js
// 封装 fetch
async function request(url, options = {}) {
  const { method = 'GET', data, headers = {}, signal } = options

  const config = {
    method,
    signal,
    headers: {
      'Content-Type': 'application/json',
      Authorization: `Bearer ${getToken()}`,
      ...headers,
    },
  }

  if (data) config.body = JSON.stringify(data)

  const response = await fetch(`${BASE_URL}${url}`, config)

  if (!response.ok) {
    const error = await response.json().catch(() => ({ message: response.statusText }))
    throw Object.assign(new Error(error.message), { status: response.status, data: error })
  }

  if (response.status === 204) return null
  return response.json()
}
```

### 17.2 请求状态管理

推荐使用 **TanStack Query（React Query）**：

```jsx
import { useQuery, useMutation, useQueryClient } from '@tanstack/react-query'

// 查询
function ProductDetail({ id }) {
  const { data: product, isLoading, error } = useQuery({
    queryKey: ['products', id],
    queryFn: () => productService.getById(id),
    staleTime: 5 * 60 * 1000, // 5分钟内不重新请求
    retry: 2,
  })

  if (isLoading) return <Skeleton />
  if (error) return <Error message={error.message} />
  return <ProductView product={product} />
}

// 变更（增删改）
function EditProductForm({ product }) {
  const queryClient = useQueryClient()

  const mutation = useMutation({
    mutationFn: (data) => productService.update(product.id, data),
    onSuccess: (updatedProduct) => {
      // 更新缓存，不需要重新请求
      queryClient.setQueryData(['products', product.id], updatedProduct)
      // 使列表缓存失效，触发重新请求
      queryClient.invalidateQueries({ queryKey: ['products'] })
      toast.success('保存成功')
    },
    onError: (error) => {
      toast.error(`保存失败: ${error.message}`)
    },
  })

  return (
    <form onSubmit={handleSubmit(data => mutation.mutate(data))}>
      {/* 表单内容 */}
      <button type="submit" disabled={mutation.isPending}>
        {mutation.isPending ? '保存中...' : '保存'}
      </button>
    </form>
  )
}
```

### 17.3 竞态问题

当多个请求并发时，后发的请求可能先返回，导致旧数据覆盖新数据：

```jsx
function SearchResults({ query }) {
  const [results, setResults] = useState([])

  useEffect(() => {
    if (!query) return

    let cancelled = false

    async function fetchResults() {
      const data = await searchAPI(query)
      // 如果这个 effect 已经被清理（query 变了），不更新 state
      if (!cancelled) setResults(data)
    }

    fetchResults()

    return () => { cancelled = true } // cleanup：标记为已取消
  }, [query])

  // 或使用 AbortController（真正取消请求）
  useEffect(() => {
    if (!query) return
    const controller = new AbortController()

    fetch(`/api/search?q=${query}`, { signal: controller.signal })
      .then(r => r.json())
      .then(setResults)
      .catch(err => {
        if (err.name !== 'AbortError') setError(err.message)
      })

    return () => controller.abort()
  }, [query])
}
```

### 17.4 副作用管理

```jsx
// 严格模式下，React 18 会双重调用 effect 来检测副作用是否可清理
// 所有 effect 必须返回清理函数

// ❌ 无法清理的副作用（严格模式会出问题）
useEffect(() => {
  fetch('/api/data').then(data => {
    setState(data) // 第二次执行时，第一次请求可能还没结束
  })
}, [])

// ✅ 可清理的副作用
useEffect(() => {
  let cancelled = false
  fetch('/api/data').then(data => {
    if (!cancelled) setState(data)
  })
  return () => { cancelled = true }
}, [])
```

---

## 18. 实战能力（最关键）

### 18.1 状态设计能力

**状态设计三原则**：
1. **最小化状态**：能派生的不要存
2. **单一数据源**：同一数据只存一处
3. **状态放对地方**：只影响本组件的放本组件，多组件共享的提升

```jsx
// ❌ 过度状态
const [items, setItems] = useState([])
const [filteredItems, setFilteredItems] = useState([]) // 可派生
const [totalCount, setTotalCount] = useState(0)        // 可派生
const [isEmpty, setIsEmpty] = useState(true)           // 可派生

// ✅ 最小化状态 + 派生
const [items, setItems] = useState([])
const [filter, setFilter] = useState('')

const filteredItems = useMemo(
  () => items.filter(item => item.name.includes(filter)),
  [items, filter]
)
const totalCount = filteredItems.length
const isEmpty = totalCount === 0
```

### 18.2 组件拆分能力

拆分时机：
- 同一组件中有多个不相关的 state → 拆分
- JSX 中某块逻辑需要独立的 state → 抽取为子组件
- 多处使用完全相同的逻辑 → 抽取为自定义 Hook 或组件

### 18.3 数据流设计

```jsx
// 数据流设计步骤：
// 1. 列出所有状态
// 2. 确定每个状态的 owner（最小公共祖先）
// 3. 通过 props 向下传，通过回调向上传
// 4. 跨层用 Context，全局用状态管理库

// 示例：电商商品页
// 状态：selectedSku, quantity, isWishlist, activeImageIndex
// - selectedSku: 被 PriceSummary + AddToCart 用，放父组件
// - quantity: 只被 AddToCart 用，放 AddToCart 内
// - isWishlist: 只被 WishlistButton 用，放 WishlistButton 内
// - activeImageIndex: 只被 Gallery 用，放 Gallery 内
```

### 18.4 异步处理

```jsx
// 完整的异步处理模式
function useAsyncAction(asyncFn) {
  const [state, setState] = useState({ loading: false, error: null, data: null })

  const execute = useCallback(async (...args) => {
    setState({ loading: true, error: null, data: null })
    try {
      const data = await asyncFn(...args)
      setState({ loading: false, error: null, data })
      return data
    } catch (err) {
      setState({ loading: false, error: err.message, data: null })
      throw err
    }
  }, [asyncFn])

  return { ...state, execute }
}

function DeleteButton({ itemId, onDeleted }) {
  const { loading, error, execute: deleteItem } = useAsyncAction(
    useCallback(() => api.delete(`/items/${itemId}`), [itemId])
  )

  async function handleClick() {
    if (!window.confirm('确认删除？')) return
    try {
      await deleteItem()
      onDeleted(itemId)
    } catch {
      // error 已在 state 中，UI 会显示
    }
  }

  return (
    <>
      <button onClick={handleClick} disabled={loading}>
        {loading ? '删除中...' : '删除'}
      </button>
      {error && <span className="error">{error}</span>}
    </>
  )
}
```

### 18.5 错误处理

```jsx
// 错误边界（Class 组件，目前还无 Hook 版本）
class ErrorBoundary extends React.Component {
  state = { hasError: false, error: null }

  static getDerivedStateFromError(error) {
    return { hasError: true, error }
  }

  componentDidCatch(error, errorInfo) {
    // 上报错误到监控系统
    Sentry.captureException(error, { extra: errorInfo })
  }

  render() {
    if (this.state.hasError) {
      return this.props.fallback || (
        <div className="error-boundary">
          <h2>出了点问题</h2>
          <p>{this.state.error?.message}</p>
          <button onClick={() => this.setState({ hasError: false, error: null })}>
            重试
          </button>
        </div>
      )
    }
    return this.props.children
  }
}

// 使用：包裹可能出错的区域
function App() {
  return (
    <ErrorBoundary fallback={<GlobalError />}>
      <Router>
        <ErrorBoundary fallback={<PageError />}>
          <Routes>
            <Route path="/" element={
              <ErrorBoundary>
                <HomePage />
              </ErrorBoundary>
            } />
          </Routes>
        </ErrorBoundary>
      </Router>
    </ErrorBoundary>
  )
}
```

---

## 19. 调试与排错

### 19.1 常见错误类型

```
1. Too many re-renders
   原因：在渲染中直接调用 setState，或 useEffect 缺少依赖导致无限循环
   排查：检查 render 函数中是否有 setState，检查 useEffect 依赖

2. Cannot update a component while rendering a different component
   原因：子组件渲染时直接调用父组件的 setState
   修复：将 setState 放入事件处理或 useEffect

3. Each child should have a unique key
   原因：列表渲染没有 key，或 key 不唯一
   修复：用稳定唯一 ID 作 key

4. Can't perform a React state update on an unmounted component
   原因：组件卸载后异步操作仍尝试 setState（React 18 已移除此警告）
   修复：useEffect 返回清理函数，取消异步操作

5. Hooks called in wrong order
   原因：在条件或循环中调用 Hook
   修复：将条件放入 Hook 内部
```

### 19.2 React DevTools

- **Components 面板**：查看组件树、props、state、hooks 当前值
- **Profiler 面板**：录制渲染，查看每个组件的渲染耗时和原因
  - "Why did this render?"：高亮显示哪个 prop/state 变化触发了渲染
- `$r`：在 Components 面板选中组件后，Console 中用 `$r` 访问组件实例

### 19.3 调试思路

```
排查步骤：

1. 状态没有更新？
   → setState 传入的是新对象/数组吗？（不能直接 mutate）
   → 是在正确的时机 setState 吗？

2. 组件渲染太多次？
   → Profiler 录制，看哪个组件渲染，原因是什么
   → 用 memo / useCallback / useMemo 优化

3. effect 执行时机不对？
   → 检查依赖数组
   → console.log 打印依赖值变化

4. 值是旧的（闭包陷阱）？
   → 改用函数式更新
   → 使用 useRef 存最新值

5. 数据没有显示？
   → 打印 props / state 确认数据存在
   → 检查条件渲染逻辑
   → 检查 key 是否导致组件被错误复用
```
