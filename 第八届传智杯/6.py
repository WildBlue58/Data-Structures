def count_substrings(s):
    """
    计算满足条件的子串数量：
    1. 不包含字符 'd'
    2. 同时包含字符 'r' 和 'e'
    """
    total = 0
    
    # 将字符串按 'd' 分割成多个连续段（不包含 'd' 的段）
    segments = []
    start = 0
    for i in range(len(s)):
        if s[i] == 'd':
            if start < i:
                segments.append(s[start:i])
            start = i + 1
    if start < len(s):
        segments.append(s[start:])
    
    # 对每个段，计算同时包含 'r' 和 'e' 的子串数量
    for segment in segments:
        if len(segment) == 0:
            continue
        
        n = len(segment)
        # 使用双指针方法
        # 对于每个左端点 left，找到最小的右端点 right，使得 segment[left:right+1] 同时包含 'r' 和 'e'
        # 那么所有以 left 开头、从 right 到 n-1 结尾的子串都满足条件
        
        # 记录每个位置之后第一个 'r' 和第一个 'e' 的位置
        # 使用滑动窗口：维护一个窗口，确保窗口内同时包含 'r' 和 'e'
        
        count_r = 0
        count_e = 0
        right = 0
        
        for left in range(n):
            # 移动 right 指针，直到窗口同时包含 'r' 和 'e'，或者 right 超出范围
            # right 指向下一个要检查的位置
            while right < n and (count_r == 0 or count_e == 0):
                if segment[right] == 'r':
                    count_r += 1
                elif segment[right] == 'e':
                    count_e += 1
                right += 1
            
            # 如果窗口同时包含 'r' 和 'e'
            # 窗口是 segment[left:right]，所有以 left 开头、从 right-1 到 n-1 结尾的子串都满足条件
            # 共 n - (right - 1) = n - right + 1 个
            if count_r > 0 and count_e > 0:
                total += (n - right + 1)
            
            # 移动 left 指针，更新计数
            if segment[left] == 'r':
                count_r -= 1
            elif segment[left] == 'e':
                count_e -= 1
    
    return total


# 读取输入
s = input().strip()

# 计算并输出结果
result = count_substrings(s)
print(result)

