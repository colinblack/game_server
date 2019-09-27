package com.sanguo.game.server.connectlogic.common.message.ProtoActivity
{
	import laya.utils.Byte;
	public class Reward4399RechargeGiftReq
	{
		public static const PROTO:String = "ProtoActivity.Reward4399RechargeGiftReq";
		public var package_root:*;
		public  var message:*;
		public var index:int;
		public function Reward4399RechargeGiftReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			index = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.index = this.index;
			return serializeObj;
		}
		public function unserialize(msgObj:*):Reward4399RechargeGiftReq
		{
			index = undefined;
			this.index = msgObj.index;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):Reward4399RechargeGiftReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}