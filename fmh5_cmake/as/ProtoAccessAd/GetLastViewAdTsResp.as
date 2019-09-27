package com.sanguo.game.server.connectlogic.common.message.ProtoAccessAd
{
	import laya.utils.Byte;
	public class GetLastViewAdTsResp
	{
		public static const PROTO:String = "ProtoAccessAd.GetLastViewAdTsResp";
		public var package_root:*;
		public  var message:*;
		public var ts:int;
		public function GetLastViewAdTsResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ts = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ts = this.ts;
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetLastViewAdTsResp
		{
			ts = undefined;
			this.ts = msgObj.ts;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetLastViewAdTsResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}