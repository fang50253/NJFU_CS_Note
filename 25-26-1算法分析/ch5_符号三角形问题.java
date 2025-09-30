public static void backtrack(int t)
{
    //如果+的个数超过half，或者当前状态下-的个数看你超过half，则返回
    if((count>half)||(t*(t-1)/2-count>half)) return;
    //当t>n时，说明已搜索到叶节点，找到一个符号三角形
    if(t>n) ++sum;//计数器增1，表示找到一个有效的符号三角形
    else
    {
        //遍历+和-的两种情况
        for(int i=0;i<2;++i)
        {
            p[1][t]=i;//设置第1行第t个元素为i
            count+=i;//更新+第个数
            //更新后续行的元素
            for(int j=2;j<=t;++j)//根据规则计算当前符号的状态
            {
                p[j][t-j+1]=p[j-1][t-j+1]^p[j-1][t-j+2];//计算当前状态
                count+=p[j][t-j+1];//更新+的个数
            }
            backtrack(t+1);//递归调用，进入下一层
            //回调，撤销当前赋值
            for(int j=2;j<=t;++j) count-=p[j][t-j+1];//撤销+的计数
            count-=i;//撤销当前选择的符号
        }
    }
}