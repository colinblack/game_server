package com.sanguo.game.server.connectlogic.common.message.ProtoOrder
{
	import laya.utils.Byte;
	public class OrderResp
	{
		public static const PROTO:String = "ProtoOrder.OrderResp";
		public var package_root:*;
		public  var message:*;
		public var order:Vector.<OrderCPP>;
		public function OrderResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			order = new Vector.<OrderCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.order = [];
			for(var i:int = 0;i < this.order.length;i++)
			{
				serializeObj.order.push(this.order[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):OrderResp
		{
			order = new Vector.<OrderCPP>();
			for(var i:int = 0;i < msgObj.order.length;i++)
			{
				this.order.push(new OrderCPP(package_root).unserialize(msgObj.order[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):OrderResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}