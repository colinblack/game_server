package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoCSMartialClubBattleResp
	{
		public static const PROTO:String = "ProtoBattle.ProtoCSMartialClubBattleResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public var info:ProtoBattleDemo;
		public function ProtoCSMartialClubBattleResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			commons = undefined;
			info = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.commons = this.commons.serialize();
			serializeObj.info = this.info.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCSMartialClubBattleResp
		{
			commons = undefined;
			info = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			this.info = new ProtoBattleDemo(package_root).unserialize(msgObj.info);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoCSMartialClubBattleResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}