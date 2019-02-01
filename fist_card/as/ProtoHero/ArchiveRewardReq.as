package com.sanguo.game.server.connectlogic.common.message.ProtoHero
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ArchiveRewardReq
	{
		public static const PROTO:String = "ProtoHero.ArchiveRewardReq";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public function ArchiveRewardReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			id = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ArchiveRewardReq
		{
			id = undefined;
			this.id = msgObj.id;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ArchiveRewardReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}