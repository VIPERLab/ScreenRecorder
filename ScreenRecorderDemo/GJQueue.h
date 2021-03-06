//
//  GJQueue.h
//  GJQueue
//
//  Created by tongguan on 16/3/15.
//  Copyright © 2016年 MinorUncle. All rights reserved.
//


#ifndef GJQueue_h
#define GJQueue_h
#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <sys/time.h>
#ifdef DEBUG
#define GJQueueLOG(format, ...) NSLog(format,##__VA_ARGS__)
#else
#define GJQueueLOG(format, ...)
#endif

#define DEFAULT_MAX_COUNT 10
#define DEFAULT_WAIT_TIME 1000



@interface  GJQueue:NSObject{

    NSMutableArray* buffer;
    long _inPointer;  //尾
    long _outPointer; //头,出的位置,左出右进,所以头尾都增长
    int _capacity;
    int _allocSize;
    
    NSLock* _lock;
    NSCondition* _outCond;
    NSCondition* _inCond;
}

    bool _unLock(pthread_mutex_t* mutex);
    void _init();
    void _resize();

#pragma mark DELEGATE

@property(nonatomic,assign)BOOL autoResize;    //是否支持自动增长，当为YES时，push永远不会等待，只会重新申请内存,默认为false

    //根据index获得value,当超过_inPointer和_outPointer范围则失败，用于遍历数组，不会产生进出队列作用
-(BOOL) getValueWithIndex:(const long)index vulue:(id*)value;

- (instancetype)initWithCapacity:(int)capacity;
//limit < 0 not wait;,unit /seconde
-(BOOL)queuePop:(id*)temBuffer limit:(NSTimeInterval)limitDuration;
-(BOOL)queuePush:(id)temBuffer limit:(NSTimeInterval)limitDuration;
-(void) clean;//主要用于线程等待时清除数据
-(int)currentLenth;
@end


#endif /* GJQueue_h */
