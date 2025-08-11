const app =getApp() /* 实例化*/
/* 页面参数 */
Page({
  /* 数据参数（自定义，在index.wxml调用参数） */
  data: {
    head_title:"首页",  /* 页面标题 */
    isConnect:false,  /* 服务器是否连接检测标识 */
    show:false, /* 弹窗开关检测标识 */
    
    show2:false,
    /* 节点数据初始化 */
    Value_1:0,
    Value_2:0,
    Value_3:0,
    Value_4:0,

    phRange: ['0','1','2','3','4','5','6','7','8','9','10','11','12','13','14'],  // 实际应生成0.0-14.0的数组
    tempRange: ['-20','-15','-10','-5','0','5','10','15','20','25','30','35','40','45','50','55','60'],  // 实际应生成-20到60的数组
    tdsRange: ['100','200','300','400','500','600','700','800','900','1000'], // 实际应生成0-2000的数组
    ntuRange: ['0','1','2','3','4','5'],    // 实际应生成0-100的数组
    
    // 当前选择索引
    phMinIndex: 0,
    phMaxIndex: 14,  // 初始对应14.0（假设phRange长度30）
    tempMinIndex: 0, // 初始对应0℃（假设tempRange从-20开始）
    tempMaxIndex: 16, // 初始对应20℃
    tdsIndex: 0,
    ntuIndex: 0,
    submitting: false ,// 提交状态
    /* 定时器参数初始化 */
    Interval: null,
    Interval2: null,
    timeOut: null,
  },
 
// PH最低值变化
phMinChange(e) {
  var that = this;
  that.setData({ phMinIndex: e.detail.value });
},

// PH最高值变化
phMaxChange(e) {
  var that = this;
  that.setData({ phMaxIndex: e.detail.value });
},

// 温度最低值变化
tempMinChange(e) {
  var that = this;
  that.setData({ tempMinIndex: e.detail.value });
},

// 温度最高值变化
tempMaxChange(e) {
  var that = this;
  that.setData({ tempMaxIndex: e.detail.value });
},

// TDS值变化
tdsChange(e) {
  var that = this;
  that.setData({ tdsIndex: e.detail.value });
},

// NTU值变化
ntuChange(e) {
  var that = this;
  that.setData({ ntuIndex: e.detail.value });
},
  setThresholds:function() {
    var that = this;
    /* 验证逻辑 */
    const phMin = Number(that.data.phRange[that.data.phMinIndex]);
    const phMax = Number(that.data.phRange[that.data.phMaxIndex]);

    const tempMin = Number(that.data.tempRange[that.data.tempMinIndex]);
    const tempMax = Number(that.data.tempRange[that.data.tempMaxIndex]);

    if (phMin >= phMax) {
      wx.showToast({ title: 'PH最高值应大于最低值', icon: 'none' });
      return;
    }
    if (tempMin >= tempMax) {
      wx.showToast({ title: '温度最高值应大于最低值', icon: 'none' });
      return;
    }

    /* 发送 request 请求 */
    that.setData({ submitting: true }); // 标记提交中
    wx.request({
      url: 'https://iot-api.heclouds.com/thingmodel/set-device-property',
      method: 'POST',
      header: {
        authorization: "version=2022-05-01&res=userid%2F396094&et=1956499200&method=md5&sign=Gx3brf28BwjRyUqDHhd%2Bbg%3D%3D"
      },
      data: {
        product_id: '87D45T0g17',
        device_name: 'H750',
        params: {
          "PH_L": parseInt(that.data.phRange[that.data.phMinIndex]),
          "PH_H": parseInt(that.data.phRange[that.data.phMaxIndex]),
          "Temperature_L": parseInt(that.data.tempRange[that.data.tempMinIndex]),
          "Temperature_H": parseInt(that.data.tempRange[that.data.tempMaxIndex]),
          "TDS_H": parseInt(that.data.tdsRange[that.data.tdsIndex]),
          "NTU_H": parseInt(that.data.ntuRange[that.data.ntuIndex])
        }
      },
      success: (res) => {
        console.log("阈值设置成功", res);
        wx.showToast({ title: '设置成功', icon: 'success' });
        that.setData({ submitting: false, show2: false });
      },
      fail: (err) => {
        console.error("阈值设置失败", err);
        wx.showToast({ title: '设置失败，请检查网络', icon: 'none' });
        that.setData({ submitting: false });
      }
    });
  },



  /* 打开Info弹窗函数 */ 
  showPopup2:function() {
    var that = this;
    that.setData({ show2: true }); /* 调用setData去修改页面参数变量 */
  },

 /* 关闭Info弹窗函数 */ 
  onClose2() {
    var that = this;
    that.setData({ show2: false });  /* 调用setData去修改页面参数变量 */
  },


  /* 打开Info弹窗函数 */ 
  showPopup:function() {
    var that = this;
    that.setData({ show: true }); /* 调用setData去修改页面参数变量 */
  },

 /* 关闭Info弹窗函数 */ 
  onClose() {
    var that = this;
    that.setData({ show: false });  /* 调用setData去修改页面参数变量 */
  },

  /* 页面初加载函数 */
  onLoad(){
    var that = this;
    that.data.Interval = setInterval(that.CheckOnenet, 5000);  /* 设置定时器(调用CheckOnenet函数，100ms) */
    that.data.Interval2 = setInterval(that.updatevalue, 5000);  /* 设置定时器(调用updatevalue函数，100ms) */
  },

 /* 检测设备是否连接函数 */ 
  CheckOnenet:function(){
   var that = this;
  /* 发送request请求 */ 
  wx.request({
     /* 官方调试API地址(具体看文档说明) */  
    url: 'https://iot-api.heclouds.com/device/detail?product_id=87D45T0g17&device_name=H750',
     /* request的操作方式(POST或者GET) */  
    method: 'GET',
    header: {
      /* 用户鉴权信息(使用token2.0生成，具体如word文档内说明) */  
      "authorization": "version=2022-05-01&res=userid%2F396094&et=1956499200&method=md5&sign=Gx3brf28BwjRyUqDHhd%2Bbg%3D%3D"
    },
    /* request执行成功后返回数据存到res */ 
    success: res =>{
      if(res.data.data.status == 1) /* 判断设备是否在线(0:不在线 1:在线) */
      {
         /* 调用setData去修改页面参数变量 */
        that.setData({
          "isConnect":true, /* isConnect修改为false */
        })
      }

    },
    /* request执行失败后返回数据存到err */
    fail: (err) => {
      console.error('错误信息：', err); /* 调试窗口显示err内的内容 */
      that.setData({
        "isConnect": false,
    });
    }
  });
  },

  /* 更新数据函数 */
  updatevalue:function(){
    /* 防止报错，先把页面this的内容传给that */
    var that = this;
    /* 发送request请求 */ 
    wx.request({
        /* 官方调试API地址(具体看文档说明)*/
        url: "https://iot-api.heclouds.com/thingmodel/query-device-property?product_id=9YyMBQhEkr&device_name=Node0",
        /* request的操作方式(POST或者GET) */ 
        method: "GET",
        header: {
          /* 用户鉴权信息(使用token2.0生成，具体如word文档内说明) */ 
          authorization: "version=2022-05-01&res=userid%2F396094&et=1956499200&method=md5&sign=Gx3brf28BwjRyUqDHhd%2Bbg%3D%3D"
        },
        /* request执行成功后返回数据存到res */ 
        success:(res)=>{
          console.log("成功",res)
          if(res.data && res.data.data && res.data.data.length >= 4)  /* 判断返回的res内的内容符合要求 */
          {
            /* 调用setData去修改页面参数变量 */
            that.setData({
              "Value_1":res.data.data[6].value,
              "Value_2":res.data.data[2].value,
              "Value_3":res.data.data[3].value,
              "Value_4":res.data.data[4].value,
              //"sensorslist[1].value":res.data.data[1].value,  /* data内数据为数组使用这种方法修改 */
              //"sensorslist[0].value":res.data.data[3].value, /* data内数据为数组使用这种方法修改 */
              /*LedisOpen:res.data.data[2].value,*/
              //chiptemperature_value:res.data.data[0].value, /* data内数据为普通变量使用这种方法修改 */
            })
          }
        },
        /* request执行失败后返回数据存到err */
        fail: (err) => {
          console.error('错误信息：', err); /* 调试窗口显示err内的内容 */
          /* 调用setData去修改页面参数变量 */
          that.data({
            isConnect:false,  /* data内数据为普通变量使用这种方法修改 */
          })
        }
      } 
    )
  },









/********************************/
/********************************/
/*** 防止定时器在后台还在死循环 ***/
/********************************/
/********************************/
  /* 页面隐藏时调用的函数 */
  onHide:function(){
    var that = this;
    if (that.data.Interval) {
      clearInterval(that.data.Interval);  /* 清空Interval数据 */
  }
  if (that.data.Interval2) {
      clearInterval(that.data.Interval2);  /* 清空Interval2数据 */
  }
  if (that.data.timeOut) {
      clearTimeout(that.data.timeOut);  /* 清空Timeout数据 */
  }
  },
  /* 页面重载时调用的函数 */
  onUnload:function(){
    var that = this;
    if (that.data.Interval) {
      clearInterval(that.data.Interval);  /* 清空Interval数据 */
  }
  if (that.data.Interval2) {
      clearInterval(that.data.Interval2);  /* 清空Interval2数据 */
  }
  if (that.data.timeOut) {
      clearTimeout(that.data.timeOut);  /* 清空Timeout数据 */
  }
  }
})
