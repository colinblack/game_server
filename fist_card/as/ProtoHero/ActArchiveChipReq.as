package com.sanguo.game.server.connectlogic.common.message.ProtoHero
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ActArchiveChipReq
	{
		public static const PROTO:String = "ProtoHero.ActArchiveChipReq";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var act:int;
		public function ActArchiveChipReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			id = undefined;
			act = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.act = this.act;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ActArchiveChipReq
		{
			id = undefined;
			act = undefined;
			this.id = msgObj.id;
			this.act = msgObj.act;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ActArchiveChipReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}