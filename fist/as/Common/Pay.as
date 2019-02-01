package com.sanguo.game.server.connectlogic.common.message.Common
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class Pay
	{
		public static const PROTO:String = "Common.Pay";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var cash:int;
		public var ts:int;
		public function Pay(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			uid = undefined;
			cash = undefined;
			ts = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			serializeObj.cash = this.cash;
			serializeObj.ts = this.ts;
			return serializeObj;
		}
		public function unserialize(msgObj:*):Pay
		{
			uid = undefined;
			cash = undefined;
			ts = undefined;
			this.uid = msgObj.uid;
			this.cash = msgObj.cash;
			this.ts = msgObj.ts;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):Pay
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}