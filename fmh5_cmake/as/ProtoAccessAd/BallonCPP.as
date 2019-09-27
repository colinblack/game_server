package com.sanguo.game.server.connectlogic.common.message.ProtoAccessAd
{
	import laya.utils.Byte;
	public class BallonCPP
	{
		public static const PROTO:String = "ProtoAccessAd.BallonCPP";
		public var package_root:*;
		public  var message:*;
		public var remainCnt:int;
		public var nextTs:int;
		public function BallonCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			remainCnt = undefined;
			nextTs = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.remainCnt = this.remainCnt;
			serializeObj.nextTs = this.nextTs;
			return serializeObj;
		}
		public function unserialize(msgObj:*):BallonCPP
		{
			remainCnt = undefined;
			nextTs = undefined;
			this.remainCnt = msgObj.remainCnt;
			this.nextTs = msgObj.nextTs;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):BallonCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}