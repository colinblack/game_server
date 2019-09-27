package com.sanguo.game.server.connectlogic.common.message.ProtoAccessAd
{
	import laya.utils.Byte;
	public class GetScarecrowInfoResp
	{
		public static const PROTO:String = "ProtoAccessAd.GetScarecrowInfoResp";
		public var package_root:*;
		public  var message:*;
		public var scarecrow:ScarecrowCPP;
		public function GetScarecrowInfoResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			scarecrow = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.scarecrow = this.scarecrow.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetScarecrowInfoResp
		{
			scarecrow = undefined;
			this.scarecrow = new ScarecrowCPP(package_root).unserialize(msgObj.scarecrow);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetScarecrowInfoResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}