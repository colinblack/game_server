package com.sanguo.game.server.connectlogic.common.message.ProtoOrder
{
	import laya.utils.Byte;
	public class DeleteOrderReq
	{
		public static const PROTO:String = "ProtoOrder.DeleteOrderReq";
		public var package_root:*;
		public  var message:*;
		public var slot:int;
		public function DeleteOrderReq(root:*)
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
		public function unserialize(msgObj:*):DeleteOrderReq
		{
			slot = undefined;
			this.slot = msgObj.slot;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):DeleteOrderReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}