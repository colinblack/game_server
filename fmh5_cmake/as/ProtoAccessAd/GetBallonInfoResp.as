package com.sanguo.game.server.connectlogic.common.message.ProtoAccessAd
{
	import laya.utils.Byte;
	public class GetBallonInfoResp
	{
		public static const PROTO:String = "ProtoAccessAd.GetBallonInfoResp";
		public var package_root:*;
		public  var message:*;
		public var ballon:BallonCPP;
		public function GetBallonInfoResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ballon = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ballon = this.ballon.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetBallonInfoResp
		{
			ballon = undefined;
			this.ballon = new BallonCPP(package_root).unserialize(msgObj.ballon);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetBallonInfoResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}