import qualified WeightedGraph as G

g1 :: G.WeightedGraph Char Int
g1 = G.mkWeigthedGraphEdges ['a','b','c','d','e']
                          [ G.WE 'a' 3 'b', G.WE 'a' 7 'd'
                          , G.WE 'b' 4 'c', G.WE 'b' 2 'd'
                          , G.WE 'c' 5 'd', G.WE 'c' 6 'e'
                          , G.WE 'd' 5 'e'
                          ]

primSpanningTree :: (Ord a) => (Ord b) => (Num b) => G.WeightedGraph a b -> G.WeightedGraph a b
primSpanningTree g = G.mkWeigthedGraphEdges (G.vertices g) (aux v [source] [])
    where
    source:_ = G.vertices g
    v = filter (/= source) (G.vertices g)

    selectMin (x:xs) = aux x xs
        where
        aux min [] = min
        aux min@(_,mv,_) (x@(_,xv,_):xs) | mv < xv = aux min xs
                                     | otherwise = aux x xs

    aux [] _ copt = copt
    aux v vopt copt = aux vv (vmin:vopt) (edge:copt)
        where
        vv = filter (/= vmin) v
        (vmin,vlen,edge) = selectMin [(dst,weight,e) | e@(G.WE org weight dst) <- (G.weigthedEdges g), ((any (==dst) v) && (any (==org) vopt))]

