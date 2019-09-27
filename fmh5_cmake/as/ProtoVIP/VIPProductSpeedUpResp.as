package com.sanguo.game.server.connectlogic.common.message.ProtoVIP
{
	import laya.utils.Byte;
	public class VIPProductSpeedUpResp
	{
		public static const PROTO:String = "ProtoVIP.VIPProductSpeedUpResp";
		public var package_root:*;
		public  var message:*;
		public var speedupUseCnt:int;
		public function VIPProductSpeedUpResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			speedupUseCnt = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.speedupUseCnt = this.speedupUseCnt;
			return serializeObj;
		}
		public function unserialize(msgObj:*):VIPProductSpeedUpResp
		{
			speedupUseCnt = undefined;
			this.speedupUseCnt = msgObj.speedupUseCnt;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):VIPProductSpeedUpResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}