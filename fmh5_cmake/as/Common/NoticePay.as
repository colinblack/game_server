package com.sanguo.game.server.connectlogic.common.message.Common
{
	import laya.utils.Byte;
	public class NoticePay
	{
		public static const PROTO:String = "Common.NoticePay";
		public var package_root:*;
		public  var message:*;
		public var cash:int;
		public var viplevel:int;
		public var accrecharge:int;
		public function NoticePay(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			cash = undefined;
			viplevel = undefined;
			accrecharge = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.cash = this.cash;
			serializeObj.viplevel = this.viplevel;
			serializeObj.accrecharge = this.accrecharge;
			return serializeObj;
		}
		public function unserialize(msgObj:*):NoticePay
		{
			cash = undefined;
			viplevel = undefined;
			accrecharge = undefined;
			this.cash = msgObj.cash;
			this.viplevel = msgObj.viplevel;
			this.accrecharge = msgObj.accrecharge;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):NoticePay
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}