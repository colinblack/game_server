package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoGetMartialClubReq
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoGetMartialClubReq";
		public var package_root:*;
		public  var message:*;
		public function ProtoGetMartialClubReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoGetMartialClubReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoGetMartialClubReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}