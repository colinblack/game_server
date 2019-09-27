package com.sanguo.game.server.connectlogic.common.message.ProtoOrder
{
	import laya.utils.Byte;
	public class OrderQueryReq
	{
		public static const PROTO:String = "ProtoOrder.OrderQueryReq";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public function OrderQueryReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):OrderQueryReq
		{
			uid = undefined;
			this.uid = msgObj.uid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):OrderQueryReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}