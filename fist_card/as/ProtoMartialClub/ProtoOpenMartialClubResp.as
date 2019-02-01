package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoOpenMartialClubResp
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoOpenMartialClubResp";
		public var package_root:*;
		public  var message:*;
		public var nextTs:int;
		public function ProtoOpenMartialClubResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			nextTs = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.nextTs = this.nextTs;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoOpenMartialClubResp
		{
			nextTs = undefined;
			this.nextTs = msgObj.nextTs;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoOpenMartialClubResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}