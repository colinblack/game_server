package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class MartialHeroInfo
	{
		public static const PROTO:String = "ProtoMartialClub.MartialHeroInfo";
		public var package_root:*;
		public  var message:*;
		public var user:MartialClubUserInfo;
		public var hero:MartialHeroBaseInfo;
		public function MartialHeroInfo(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			user = undefined;
			hero = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.user = this.user.serialize();
			serializeObj.hero = this.hero.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):MartialHeroInfo
		{
			user = undefined;
			hero = undefined;
			this.user = new MartialClubUserInfo(package_root).unserialize(msgObj.user);
			this.hero = new MartialHeroBaseInfo(package_root).unserialize(msgObj.hero);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):MartialHeroInfo
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}