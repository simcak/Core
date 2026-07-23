import { type ReactNode, useState } from 'react'
import { cn } from '@/lib/utils.ts'
import { useTranslation } from 'react-i18next'

import {
  Table,
  TableBody,
  TableCell,
  TableHead,
  TableHeader,
  TableRow,
} from '@/components/ui/table.tsx'

import {
  type ColumnDef,
  type ColumnFiltersState,
  type SortingState,
  flexRender,
  getCoreRowModel,
  getFilteredRowModel,
  useReactTable,
  getPaginationRowModel,
  getSortedRowModel,
} from '@tanstack/react-table'

import {
  ContextMenu,
  ContextMenuTrigger,
  ContextMenuContent,
} from '@/components/ui/context-menu.tsx'

import { Button } from '@/components/ui/button.tsx'
import { Input } from '@/components/ui/input.tsx'

interface DataTableProps<TData, TValue> {
  columns: ColumnDef<TData, TValue>[]
  data: TData[]
  emptyMessage?: string | undefined
  filterColumns?: string[]
  filterPlaceholder?: string
  onRowClick?: (row: TData) => void
  rowClassName?: (row: TData) => string | undefined
  renderContextMenu?: (row: TData) => ReactNode
}

export function DataTable<TData, TValue>({
  columns,
  data,
  emptyMessage,
  filterColumns,
  filterPlaceholder,
  onRowClick,
  rowClassName,
  renderContextMenu,
}: DataTableProps<TData, TValue>) {
  'use no memo'

  const { t } = useTranslation()
  const [sorting, setSorting] = useState<SortingState>([])
  const [columnFilters, setColumnFilters] = useState<ColumnFiltersState>([])
  const [globalFilter, setGlobalFilter] = useState('')
  // eslint-disable-next-line react-hooks/incompatible-library
  const table = useReactTable({
    data,
    columns,
    getCoreRowModel: getCoreRowModel(),
    getFilteredRowModel: getFilteredRowModel(),
    getPaginationRowModel: getPaginationRowModel(),
    getSortedRowModel: getSortedRowModel(),
    onColumnFiltersChange: setColumnFilters,
    onGlobalFilterChange: setGlobalFilter,
    onSortingChange: setSorting,
    globalFilterFn: (row, _columnId, filterValue) => {
      if (!filterValue || !filterColumns?.length) return true
      return filterColumns.some((columnId) => {
        const cellValue = row.getValue(columnId)
        return String(cellValue ?? '')
          .toLowerCase()
          .includes(String(filterValue).toLowerCase())
      })
    },
    state: {
      sorting,
      columnFilters,
      globalFilter,
    },
  })

  return (
    <div>
      {filterColumns && (
        <div className="flex items-center py-4">
          <Input
            placeholder={filterPlaceholder ?? 'Filter ...'}
            value={globalFilter ?? ''}
            onChange={(event) => setGlobalFilter(event.target.value)}
            className="max-w-sm"
          />
        </div>
      )}
      <div className="rounded-md border overflow-x-auto">
        <Table>
          <TableHeader>
            {table.getHeaderGroups().map((headerGroup) => (
              <TableRow key={headerGroup.id}>
                {headerGroup.headers.map((header) => {
                  return (
                    <TableHead key={header.id}>
                      {header.isPlaceholder
                        ? null
                        : flexRender(header.column.columnDef.header, header.getContext())}
                    </TableHead>
                  )
                })}
              </TableRow>
            ))}
          </TableHeader>
          <TableBody>
            {table.getRowModel().rows?.length ? (
              table.getRowModel().rows.map((row) => (
                <ContextMenu key={row.id}>
                  <ContextMenuTrigger asChild>
                    <TableRow
                      onClick={() => onRowClick?.(row.original)}
                      className={cn(
                        onRowClick ? 'cursor-pointer' : undefined,
                        rowClassName?.(row.original)
                      )}
                      data-state={row.getIsSelected() && 'selected'}
                    >
                      {row.getVisibleCells().map((cell) => (
                        <TableCell key={cell.id}>
                          {flexRender(cell.column.columnDef.cell, cell.getContext())}
                        </TableCell>
                      ))}
                    </TableRow>
                  </ContextMenuTrigger>
                  <ContextMenuContent>{renderContextMenu?.(row.original)}</ContextMenuContent>
                </ContextMenu>
              ))
            ) : (
              <TableRow>
                <TableCell colSpan={columns.length} className="h-24 text-center">
                  {emptyMessage ?? t('common.noData')}
                </TableCell>
              </TableRow>
            )}
          </TableBody>
        </Table>
      </div>
      {table.getPageCount() > 1 && (
        <div className="flex items-center justify-end space-x-2 py-4">
          <Button
            variant="outline"
            size="sm"
            onClick={() => table.previousPage()}
            disabled={!table.getCanPreviousPage()}
          >
            {t('common.previous')}
          </Button>
          <Button
            variant="outline"
            size="sm"
            onClick={() => table.nextPage()}
            disabled={!table.getCanNextPage()}
          >
            {t('common.next')}
          </Button>
        </div>
      )}
    </div>
  )
}
