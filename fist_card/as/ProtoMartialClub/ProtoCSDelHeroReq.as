package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoCSDelHeroReq
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoCSDelHeroReq";
		public var package_root:*;
		public  var message:*;
		public var ownerUid:int;
		public var heroId:int;
		public function ProtoCSDelHeroReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			ownerUid = undefined;
			heroId = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ownerUid = this.ownerUid;
			serializeObj.heroId = this.heroId;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCSDelHeroReq
		{
			ownerUid = undefined;
			heroId = undefined;
			this.ownerUid = msgObj.ownerUid;
			this.heroId = msgObj.heroId;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoCSDelHeroReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}