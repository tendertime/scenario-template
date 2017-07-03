opt是贪心得到的结果.
其中chinatelecom是chinanet的拓扑
agis是美国骨干网
geant是欧洲骨干网
然后agis和geant是有带宽的,chinanet只有位置信息;

目前第一轮,zipf的beta采用默认0.7;结果包括了cachesize和总缓存大小.
仿真运行时间是5s.每个节点产生1个数据包.每个节点的缓存容量为10;

改成每秒38(chinanet一共38个节点),发生了1472次hit.(这种38*38也不正常吧??)
所以zipf分布的参数到底是什么鬼...

agis就更可怕了...25个节点 每秒25个interest,发生了1071次hit.
(就目前情况,每结点10个cache是很不科学的...应该给少一点 再说吧,你很难给一个具体的指标)
结果彻底出来再说吧...

geant发生了1680次hit.嗯 毕竟37个node 已经接近chinanet了23333













