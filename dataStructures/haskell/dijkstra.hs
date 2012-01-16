import qualified WeightedGraph as G
import qualified Dictionary as D

g1 :: G.WeightedGraph Char Int
g1 = G.mkWeigthedGraphEdges ['a','b','c','d','e']
                          [ G.WE 'a' 3 'b', G.WE 'a' 7 'd'
                          , G.WE 'b' 4 'c', G.WE 'b' 2 'd'
                          , G.WE 'c' 5 'd', G.WE 'c' 6 'e'
                          , G.WE 'd' 5 'e'
                          ]

fuckOffImFuckingSureThisWillNotReturnNothing :: (Maybe a) -> a
fuckOffImFuckingSureThisWillNotReturnNothing (Just x) = x
fuckOffImFuckingSureThisWillNotReturnNothing (Nothing) = error ("Cosmic rays caused the CPU to make an error. " ++
                                                               "Or the author of this program is stupid. " ++
                                                               "But the first one is more probable (According to the author of this program)")


shortestLengths :: (Ord a) => (Ord b) => (Num b) => G.WeightedGraph a b -> a -> D.Dictionary a b
shortestLengths g source = aux v [source] copt
    where
    v = filter (/= source) (G.vertices g)
    copt = D.insert source 0 D.empty

    selectMin (x:xs) = aux x xs
        where
        aux min [] = min
        aux min@(_,mv) (x@(_,xv):xs) | mv < xv = aux min xs
                                     | otherwise = aux x xs

    aux [] _ copt = copt
    aux v vopt copt = aux vv (vmin:vopt) (D.insert vmin vlen copt)
        where
        vv = filter (/= vmin) v
        (vmin,vlen) = selectMin [(dst,weight + (fuckOffImFuckingSureThisWillNotReturnNothing (D.valueOf org copt))) | (G.WE org weight dst) <- (G.weigthedEdges g), ((any (==dst) v) && (any (==org) vopt))]

