import qualified Graph as G
import qualified Dictionary as D
import Data.Maybe

g1 = G.mkGraphEdges ['a','b','c','d','e']
                    [('a','b'),('b','c'),('c')]
                          --[('a','b') ,('a','d')
                          --,('b','c'), ('b','d')
                          --,('c','d'), ('c','e')
                          --,('d','e')
                          --]
data Color = Red | Blue | Uncolored deriving Eq

isBipartite :: (Ord a) => G.Graph a -> Bool
isBipartite g = aux g (uncoloredDict (G.vertices g)) Blue source
    where
    source:_ = G.vertices g
    uncoloredDict [] = D.empty
    uncoloredDict (x:xs) = D.insert x Uncolored (uncoloredDict xs)

    aux :: (Ord a) => G.Graph a -> D.Dictionary a Color -> Color -> a -> Bool
    aux g dict color s
       | any (vertexIsOfColor color) (G.successors g s) = False
       | otherwise = and (map (aux g newdict (othercolor color)) uncoloredSuccessors)
       where
       othercolor Red = Blue
       othercolor Blue = Red

       vertexIsOfColor color vertex = (fromJust (D.valueOf vertex dict)) == color

       newdict = D.insert s color dict
       uncoloredSuccessors = filter (isUncolored dict) (G.successors g s)
           where isUncolored dict vertex = (fromJust (D.valueOf vertex dict)) == Uncolored

