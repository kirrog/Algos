{$Q+,R+,O-}
{$APPTYPE CONSOLE}
uses
  SysUtils;

const
  MAXM = 100000;
  MAXFREE = MAXM div 2;

type
  int = longint;

const
  HASHN = 5667239;

var
  head: array[0..HASHN] of int;
  key, val, next: array[1..4 * MAXFREE] of int;
  len: int = 0;

function hash(k: int): int;
begin
  result := abs(k) mod HASHN;
end;

procedure hashadd(k, v: int);
var
  ind: int;
begin
  ind := hash(k);
  inc(len);
  key[len] := k;
  val[len] := v;
  next[len] := head[ind];
  head[ind] := len;
end;

procedure hashdelete(k: int);
var
  ind: int;
begin
  ind := hash(k);
  if (key[head[ind]] = k) then
  begin
    head[ind] := next[head[ind]];
    exit;
  end;
  ind := head[ind];
  while (key[next[ind]] <> k) do
  begin
    ind := next[ind];
  end;
  next[ind] := next[next[ind]];
end;

function hashfind(k: int): int;
begin
  result := head[hash(k)];
  while (result > 0) and (key[result] <> k) do
    result := next[result];
  if (result > 0) then
    result := val[result];
end;

var
  i, n, m, t: int;
  hsize: int;
  heap, hpos: array[1..MAXFREE] of int;
  mx, my: array[1..MAXM] of int;
  frees: int;
  fx, fl: array[1..MAXFREE] of int;

procedure swap(a, b: int);
var
  c: int;
begin
  c := heap[a];
  heap[a] := heap[b];
  heap[b] := c;
  hpos[heap[a]] := a;
  hpos[heap[b]] := b;
end;

procedure siftup(v: int);
begin
  if (v > 1) and (fl[heap[v]] > fl[heap[v div 2]]) then
  begin
    swap(v, v div 2);
    siftup(v div 2);
  end;
end;

procedure siftdown(v: int);
begin
  if (2 * v + 1 <= hsize) and (fl[heap[2 * v + 1]] > fl[heap[v]]) and
     (fl[heap[2 * v + 1]] > fl[heap[2 * v]]) then
  begin
    swap(v, 2 * v + 1);
    siftdown(2 * v + 1);
  end
  else if (2 * v <= hsize) and (fl[heap[2 * v]] > fl[heap[v]]) then
  begin
    swap(v, 2 * v);
    siftdown(2 * v);
  end;
end;

procedure AddFree(x, y: int);
var
  f: int;
begin
  f := hashfind({false,} y + 1);
  if (f > 0) then
  begin
    hashdelete(y + 1);
    inc(y, fl[f]);
    fl[f] := 0;
    siftdown(hpos[f]);
    hashdelete(-y);
  end;
  f := hashfind({true,} -(x - 1));
  if (f > 0) then
  begin
    hashdelete(-(x - 1));
    x := fx[f];
    fl[f] := 0;
    siftdown(hpos[f]);
    hashdelete(x);
  end;
  inc(frees);
  fx[frees] := x;
  fl[frees] := y + 1 - x;
  inc(hsize);
  heap[hsize] := frees;
  hpos[frees] := hsize;
  siftup(hsize);
  hashadd({false,} x, frees);
  hashadd({true,} -y, frees);
end;

begin
  reset(input, 'memory.in');
  rewrite(output, 'memory.out');
  read(n, m);
  AddFree(1, n);
  for i := 1 to m do
  begin
    read(t);
    if (t > 0) then
    begin
      if (hsize > 0) and (fl[heap[1]] >= t) then
      begin
        mx[i] := fx[heap[1]];
        my[i] := mx[i] + t - 1;
        writeln(mx[i]);
        hashdelete(fx[heap[1]]);
        inc(fx[heap[1]], t);
        hashadd(fx[heap[1]], heap[1]);
        dec(fl[heap[1]], t);
        siftdown(1);
      end
      else
        writeln(-1);
    end
    else if (mx[-t] > 0) then
    begin
      AddFree(mx[-t], my[-t]);
    end;
  end;
end.