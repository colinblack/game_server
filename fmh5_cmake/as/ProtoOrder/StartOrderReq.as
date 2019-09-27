package com.sanguo.game.server.connectlogic.common.message.ProtoOrder
{
	import laya.utils.Byte;
	public class StartOrderReq
	{
		public static const PROTO:String = "ProtoOrder.StartOrderReq";
		public var package_root:*;
		public  var message:*;
		public var slot:int;
		public function StartOrderReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			slot = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.slot = this.slot;
			return serializeObj;
		}
		public function unserialize(msgObj:*):StartOrderReq
		{
			slot = undefined;
			this.slot = msgObj.slot;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):StartOrderReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}