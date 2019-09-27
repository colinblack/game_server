package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class CostCashResp
	{
		public static const PROTO:String = "User.CostCashResp";
		public var package_root:*;
		public  var message:*;
		public var cash:int;
		public var operation:int;
		public function CostCashResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			cash = undefined;
			operation = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.cash = this.cash;
			serializeObj.operation = this.operation;
			return serializeObj;
		}
		public function unserialize(msgObj:*):CostCashResp
		{
			cash = undefined;
			operation = undefined;
			this.cash = msgObj.cash;
			this.operation = msgObj.operation;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CostCashResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}