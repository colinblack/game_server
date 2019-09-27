package com.sanguo.game.server.connectlogic.common.message.ProtoOrder
{
	import laya.utils.Byte;
	public class OrderADBonusCPP
	{
		public static const PROTO:String = "ProtoOrder.OrderADBonusCPP";
		public var package_root:*;
		public  var message:*;
		public var viewedAdCnt:int;
		public var remianAdBonusCnt:int;
		public function OrderADBonusCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			viewedAdCnt = undefined;
			remianAdBonusCnt = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.viewedAdCnt = this.viewedAdCnt;
			serializeObj.remianAdBonusCnt = this.remianAdBonusCnt;
			return serializeObj;
		}
		public function unserialize(msgObj:*):OrderADBonusCPP
		{
			viewedAdCnt = undefined;
			remianAdBonusCnt = undefined;
			this.viewedAdCnt = msgObj.viewedAdCnt;
			this.remianAdBonusCnt = msgObj.remianAdBonusCnt;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):OrderADBonusCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}