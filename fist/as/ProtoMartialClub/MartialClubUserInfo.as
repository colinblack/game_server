package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class MartialClubUserInfo
	{
		public static const PROTO:String = "ProtoMartialClub.MartialClubUserInfo";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var name:String;
		public var fig:String;
		public var level:int;
		public var grade:int;
		public function MartialClubUserInfo(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			uid = undefined;
			name = undefined;
			fig = undefined;
			level = undefined;
			grade = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			serializeObj.name = this.name;
			serializeObj.fig = this.fig;
			if(this.level!= undefined)
			{
				serializeObj.level = this.level;
			}
			if(this.grade!= undefined)
			{
				serializeObj.grade = this.grade;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):MartialClubUserInfo
		{
			uid = undefined;
			name = undefined;
			fig = undefined;
			level = undefined;
			grade = undefined;
			this.uid = msgObj.uid;
			this.name = msgObj.name;
			this.fig = msgObj.fig;
			if(msgObj.hasOwnProperty("level"))
			{
				this.level = msgObj.level;
			}
			if(msgObj.hasOwnProperty("grade"))
			{
				this.grade = msgObj.grade;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):MartialClubUserInfo
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}