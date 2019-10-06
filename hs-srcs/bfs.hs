-- (https://github.com/charles-cooper/hackerrank/blob/master/algorithms/graph-theory/bfs.hs)
-- Solution to https://www.hackerrank.com/challenges/bfsshortreach
-- This program takes input from stdin
-- which specifies test cases of graphs and start nodes.
-- For each test case, this program prints the distances
-- between the start node and each node in the graph,
-- which are defined as (6*) the number of steps to reach the target node,
-- or -1 for unreachable nodes.
import Data.Functor
import Control.Monad
import Data.Function
import qualified Data.IntMap as Map
import Data.Tuple (swap)
import Data.List (intercalate, delete)

type Node     = Int
type Distance = Int
type Graph    = Map.IntMap [Node]
type Solution = Map.IntMap Distance

data TestCase = TestCase
  { numNodes  :: Int
  , numEdges  :: Int
  , edgeList  :: [(Node,Node)]
  , startNode :: Node
  } deriving Show

readTestCase :: IO TestCase
readTestCase = do
  [n,m] <- map read <$> words <$> getLine
  edges <- replicateM m $ do
    [x,y] <- map read <$> words <$> getLine
    return (x,y)
  start <- read <$> getLine
  return $ TestCase n m edges start

-- mkGraph takes a list of directed edges and creates an undirected graph.
-- Returns:
--   A lookup table which maps nodes to a list of its neighbors.
--   The table is sparse, so a node with no neighbors is not in the table.
mkGraph :: [(Node, Node)] -> Graph
mkGraph edges = let
  bidirectional = edges ++ (map swap edges)
  in Map.fromListWith (++) $ map (\(a,b) -> (a,[b])) bidirectional

-- Returns:
--   The neighbors of a node in a graph as a list.
--   If the node has no neighbors the empty list is returned
neighborsOf :: Graph -> Node -> [Node]
neighborsOf graph n = Map.findWithDefault [] n graph

-- bfs takes a graph and a start node, and finds the shortest distances
-- to all nodes which can be reached from the start node, using BFS.
-- Returns:
--   A lookup table mapping nodes to their distances from the start node.
--   Unreachable nodes will not be in the table.
bfs :: Graph -> Node -> Solution

bfs graph start = step [start] 0 (Map.singleton start 0)

  where

  step :: [Node] -> Distance -> Solution -> Solution

  step [] _ solution       = solution
  step nodes dist visited  = let
    -- for each node at the current distance,
    -- find all (unique) neighbors that have not yet been visited.
    -- and mark each neighbor as being (current distance + 1) from root
    --
    -- (if a neighbor has not yet been visited,
    -- then by definition we have just found
    -- the shortest path to that neighbor)
    toVisit =
      concatMap (\n -> graph `neighborsOf` n) nodes
        & map (\node -> (node, dist + 1)) -- mark distance
        & Map.fromList                    -- unique
        & flip Map.difference visited     -- not yet visited

    -- merge newly found distances into solution, and then repeat
    visited' = Map.union visited toVisit
    in step (Map.keys toVisit) (dist + 1) visited'

solve :: TestCase -> Solution
solve inp = bfs
  (mkGraph $ edgeList inp)
  (startNode inp)

for :: [a] -> (a -> b) -> [b]
for = flip map

-- mkOutput takes a solution and prepares it for
-- pretty printing in the output format
mkOutput :: Int -> Int -> Solution -> [Int]
mkOutput n startNode solution =
  for (delete startNode [1..n]) $ \i ->
    case Map.lookup i solution of
      Nothing -> -1
      Just t  -> 6*t

main = do
  t <- read <$> getLine
  replicateM t $ do
    c <- readTestCase
    putStrLn
      $ intercalate " " . map show
      $ mkOutput (numNodes c) (startNode c) (solve c)

