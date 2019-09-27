package com.sanguo.game.server.connectlogic.common.message.ProtoOrder
{
	import laya.utils.Byte;
	public class DeleteOrderResp
	{
		public static const PROTO:String = "ProtoOrder.DeleteOrderResp";
		public var package_root:*;
		public  var message:*;
		public var result:Boolean;
		public var order:OrderCPP;
		public function DeleteOrderResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			result = undefined;
			order = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.result = this.result;
			serializeObj.order = this.order.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):DeleteOrderResp
		{
			result = undefined;
			order = undefined;
			this.result = msgObj.result;
			this.order = new OrderCPP(package_root).unserialize(msgObj.order);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):DeleteOrderResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}