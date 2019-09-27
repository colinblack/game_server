package com.sanguo.game.server.connectlogic.common.message.ProtoVIP
{
	import laya.utils.Byte;
	public class VIPProductSpeedUpReq
	{
		public static const PROTO:String = "ProtoVIP.VIPProductSpeedUpReq";
		public var package_root:*;
		public  var message:*;
		public var ud:int;
		public function VIPProductSpeedUpReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ud = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ud = this.ud;
			return serializeObj;
		}
		public function unserialize(msgObj:*):VIPProductSpeedUpReq
		{
			ud = undefined;
			this.ud = msgObj.ud;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):VIPProductSpeedUpReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}