package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class CostCashReq
	{
		public static const PROTO:String = "User.CostCashReq";
		public var package_root:*;
		public  var message:*;
		public var cash:int;
		public var opCode:String;
		public var operation:int;
		public function CostCashReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			cash = undefined;
			opCode = undefined;
			operation = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.cash = this.cash;
			serializeObj.opCode = this.opCode;
			serializeObj.operation = this.operation;
			return serializeObj;
		}
		public function unserialize(msgObj:*):CostCashReq
		{
			cash = undefined;
			opCode = undefined;
			operation = undefined;
			this.cash = msgObj.cash;
			this.opCode = msgObj.opCode;
			this.operation = msgObj.operation;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CostCashReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}