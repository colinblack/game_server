package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoGetOwnerClubResp
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoGetOwnerClubResp";
		public var package_root:*;
		public  var message:*;
		public var info:SingleMartialClub;
		public function ProtoGetOwnerClubResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			info = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.info = this.info.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoGetOwnerClubResp
		{
			info = undefined;
			this.info = new SingleMartialClub(package_root).unserialize(msgObj.info);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoGetOwnerClubResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}