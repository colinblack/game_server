package com.sanguo.game.server.connectlogic.common.message.ProtoOrder
{
	import laya.utils.Byte;
	public class GetOrderBonusInfoReq
	{
		public static const PROTO:String = "ProtoOrder.GetOrderBonusInfoReq";
		public var package_root:*;
		public  var message:*;
		public function GetOrderBonusInfoReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetOrderBonusInfoReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetOrderBonusInfoReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}